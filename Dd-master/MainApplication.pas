unit MainApplication;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, TOperativeUnit, ComCtrls, StdCtrls, DateUtils, FormAdd, FormEdit,
  System.RegularExpressions, Vcl.ExtCtrls, TWatermarkEditUnit;

procedure Append(item: TElemType);
stdcall external 'LinkedList.dll' name 'Append';
procedure WriteEach;
stdcall external 'LinkedList.dll' name 'WriteEach';
procedure Seed;
stdcall external 'LinkedList.dll' name 'Seed';
procedure WriteToFile;
stdcall external 'LinkedList.dll' name 'WriteToFile';
procedure ReadFromFile;
stdcall external 'LinkedList.dll' name 'ReadFromFile';
function GetHead: PElem;
stdcall external 'LinkedList.dll' name 'GetHead';
function EqualTOperatives: PElem;
stdcall external 'LinkedList.dll' name 'EqualTOperatives';
procedure Remove(op: TOperative);
stdcall external 'LinkedList.dll' name 'Remove';
procedure UpdateOperative(a, b: TOperative); stdcall;
  external 'LinkedList.dll' name 'UpdateOperative';

type
  TMainForm = class(TForm)
    lvOperatives: TListView;
    btnDelete: TButton;
    btnAddOperative: TButton;
    btnEdit: TButton;
    btnSave: TButton;
    Label1: TLabel;
    Label2: TLabel;
    tbSearchNickName: TWatermarkEdit;
    tbSearchLastName: TWatermarkEdit;
    procedure FormCreate(Sender: TObject);
    procedure btnAddOperativeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure lvOperativesColumnClick(Sender: TObject; Column: TListColumn);
    procedure lvOperativesCompare(Sender: TObject; Item1, Item2: TListItem;
      Data: Integer; var Compare: Integer);
    procedure lvOperativesSelectItem(Sender: TObject; item: TListItem;
      Selected: Boolean);
    procedure btnEditClick(Sender: TObject);
    procedure btnSaveClick(Sender: TObject);
    procedure FormCloseQuery(Sender: TObject; var CanClose: Boolean);
    procedure tbSearchNickNameChanged(Sender: TObject);
    procedure tbSearchLastNameChanged(Sender: TObject);
  private
    SortDescending: Bool;
    SortColumn: Integer;
    PendingChanges: Bool;
    DefaultImagePath : String;
    procedure FillListBox;
    procedure FilterListBox;
    function OperativeFromSelected: TOperative;
  public
    { Public declarations }
  end;

var
  MainForm: TMainForm;

implementation

{$R *.dfm}

procedure TMainForm.FormCloseQuery(Sender: TObject; var CanClose: Boolean);
var
  dialogResult: Integer;
begin
  if PendingChanges = True then
  begin
    dialogResult := MessageDlg('Zapisać zmiany?', mtConfirmation,
      mbYesNoCancel, 0);
    if dialogResult = mrYes then
    begin
      WriteToFile;
      CanClose := True;
    end;
    if dialogResult = mrNo then
    begin
      CanClose := True;
    end;
    if dialogResult = mrCancel then
    begin
      CanClose := False;
    end;
  end;
end;

procedure TMainForm.FormCreate(Sender: TObject);
begin
  DefaultImagePath := GetCurrentDir + '\\default.bmp';
  ReadFromFile;
  PendingChanges := False;

  tbSearchNickName.Watermark := 'Pseudonim';
  tbSearchNickName.Clear;

  tbSearchLastName.Watermark := 'Nazwisko';
  tbSearchLastName.Clear;

  FillListBox;

  tbSearchNickName.CallFocusLost;
  tbSearchLastName.CallFocusLost;
end;

procedure TMainForm.lvOperativesColumnClick(Sender: TObject;
  Column: TListColumn);
begin
  TListView(Sender).SortType := stData;
  if Column.Index <> SortColumn then
  begin
    SortColumn := Column.Index;
    SortDescending := False;
  end
  else
  begin
    SortDescending := not SortDescending;
    TListView(Sender).SortType := stData;
  end;

  lvOperatives.AlphaSort;

end;

procedure TMainForm.lvOperativesCompare(Sender: TObject;
  Item1, Item2: TListItem; Data: Integer; var Compare: Integer);
begin
  if SortColumn = 0 then
  begin
    Compare := CompareText(Item1.Caption, Item2.Caption)
  end
  else if SortColumn = 3 then
  begin
    Compare := CompareDate(StrToDate(Item1.SubItems[2]),
      StrToDate(Item2.SubItems[2]));

  end
  else
  begin
    Compare := CompareText(Item1.SubItems[SortColumn - 1],
      Item2.SubItems[SortColumn - 1]);
  end;

  if SortDescending then
    Compare := -Compare;

end;

procedure TMainForm.lvOperativesSelectItem(Sender: TObject; item: TListItem;
  Selected: Boolean);
var
   op : TOperative;
begin
  btnEdit.Enabled := Selected;
  btnDelete.Enabled := Selected;
end;

procedure TMainForm.FillListBox;
var
  iter: PElem;
  item: TListItem;
begin
  FilterListBox;

end;

procedure TMainForm.FilterListBox;
var
  lastName, nickName: string;
  iter: PElem;
  item: TListItem;
  regexp1, regexp2: TRegEx;
begin
lastName := tbSearchLastName.GetValue;
nickName := tbSearchNickName.GetValue;
  if lastName.Length or nickName.Length > 0 then
  begin
    lvOperatives.Items.Clear;
    iter := GetHead;
    if lastName = '' then
       lastName := '.*';
    if nickName = '' then
       nickName := '.*';
    
    regexp1.Create(lastName, [roIgnoreCase]);
    regexp2.Create(nickName, [roIgnoreCase]);

    while iter <> nil do
    begin
      if regexp1.IsMatch(iter^.Val.LastName) and
         regexp2.IsMatch(iter^.Val.NickName) then
      begin

        item := lvOperatives.Items.Add;
        item.Caption := iter^.Val.FirstName;
        item.SubItems.Add(iter^.Val.LastName);
        item.SubItems.Add(iter^.Val.NickName);
        item.SubItems.Add(DateToStr(iter^.Val.DateOfBirth));
        item.SubItems.Add(iter^.Val.BirthPlace);
      end;
      iter := iter^.Next;
    end;
  end
  else
  begin
  lvOperatives.Clear;
  iter := GetHead;
       while iter <> nil do
  begin
    item := lvOperatives.Items.Add;
    item.Caption := iter^.Val.FirstName;
    item.SubItems.Add(iter^.Val.LastName);
    item.SubItems.Add(iter^.Val.NickName);
    item.SubItems.Add(DateToStr(iter^.Val.DateOfBirth));
    item.SubItems.Add(iter^.Val.BirthPlace);

    iter := iter^.Next;
  end;
  end;

end;

procedure TMainForm.btnAddOperativeClick(Sender: TObject);
var
  row: TOperative;
begin
  FormAdd.Form1.ShowModal;
  FillListBox;
  if FormAdd.Form1.HasAdded then
  begin
    PendingChanges := True;
  end;
  tbSearchLastName.CallFocusLost;
end;

function TMainForm.OperativeFromSelected: TOperative;
var
  op: TOperative;
  i: Integer;
begin
  for i := 0 to lvOperatives.Items.Count - 1 do
  begin
    if lvOperatives.Items[i].Selected then // DAFUQ
    begin
      op.FirstName := lvOperatives.Items[i].Caption;
      op.LastName := lvOperatives.Items[i].SubItems[0];
      op.NickName := lvOperatives.Items[i].SubItems[1];
      op.DateOfBirth := StrToDate(lvOperatives.Items[i].SubItems[2]);
      op.BirthPlace := lvOperatives.Items[i].SubItems[3];
      Result := op;
      Exit;
    end;
  end;
end;

procedure TMainForm.tbSearchLastNameChanged(Sender: TObject);
begin
  FilterListBox();
  //tbSearchNickName.CallFocusLost;
end;
procedure TMainForm.tbSearchNickNameChanged(Sender: TObject);
begin
  FilterListBox();
  //tbSearchLastName.CallFocusLost;
end;

procedure TMainForm.btnDeleteClick(Sender: TObject);
var
  op: TOperative;
  dlgResult: Integer;
begin
  if lvOperatives.Selected <> nil then
  begin
    dlgResult := MessageDlg('Na pewno usunąć?', mtConfirmation, mbYesNo, 0);
    if dlgResult = mrYes then
    begin
      op := OperativeFromSelected;
      Remove(op);
      FillListBox;
      PendingChanges := True;
    end;
  end;
  btnDelete.Enabled := False;
  btnEdit.Enabled := False;
  tbSearchLastName.CallFocusLost;
end;

procedure TMainForm.btnEditClick(Sender: TObject);
var
  row, old: TOperative;
begin
  if lvOperatives.Selected = nil then
     Exit;

  old := OperativeFromSelected;
  FormEdit.Form2.OperativeBeingEdited := @row;
  FormEdit.Form2.edtFirstName.Text := old.FirstName;
  FormEdit.Form2.edtLastName.Text := old.LastName;
  FormEdit.Form2.edtNickName.Text := old.NickName;
  FormEdit.Form2.dtpBirthDate.Date := old.DateOfBirth;
  FormEdit.Form2.edtPlaceOfBirth.Text := old.BirthPlace;

  FormEdit.Form2.DialogResult := False;
  FormEdit.Form2.ShowModal;

  if FormEdit.Form2.DialogResult = True then
  begin
    UpdateOperative(old, row);
    PendingChanges := True;
  end;

  FillListBox;
  tbSearchLastName.CallFocusLost;
end;

procedure TMainForm.btnSaveClick(Sender: TObject);
begin
  WriteToFile;
  ShowMessage('Zapisano');
  tbSearchNickName.CallFocusLost;
  PendingChanges := False;
end;

end.
