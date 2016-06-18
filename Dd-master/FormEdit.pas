unit FormEdit;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.ComCtrls,
  System.RegularExpressions, DateUtils, Types, TOperativeUnit, Vcl.ExtDlgs;

procedure Append(item : TElemType); stdcall
	external 'LinkedList.dll' name 'Append';

type
  TForm2 = class(TForm)
    edtFirstName: TEdit;
    Label1: TLabel;
    edtLastName: TEdit;
    edtNickName: TEdit;
    edtPlaceOfBirth: TEdit;
    dtpBirthDate: TDateTimePicker;
    Nazwisko: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    epFirstName: TLabel;
    epLastName: TLabel;
    epNickName: TLabel;
    epDateOfBirth: TLabel;
    epPlaceOfBirth: TLabel;
    btnAdd: TButton;
    btnClose: TButton;
    procedure btnAddClick(Sender: TObject);
    procedure btnCloseClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    function ValidateForm : Boolean;
  public
    OperativeBeingEdited : POperative;
    DialogResult : Boolean;
  end;

var
  Form2: TForm2;

implementation

function TForm2.ValidateForm: Boolean;
var
isValid, tmp : Boolean;
namePattern : string;
regex : TRegEx;
begin
     isValid := True;
     namePattern := '^[a-zA-z\-\ Œ£êó³œ¹¿Ÿæñ]+$';
     regex.Create(namePattern);

     tmp := regex.IsMatch(edtFirstName.Text, namePattern);
     epFirstName.Visible := not tmp;
     isValid := isValid and tmp;

     tmp := regex.IsMatch(edtLastName.Text);
     epLastName.Visible := not tmp;
     isValid := isValid and tmp;

     tmp := regex.IsMatch(edtNickName.Text);
     epNickName.Visible := not tmp;
     isValid := isValid and tmp;

     tmp := regex.IsMatch(edtPlaceOfBirth.Text);
     epPlaceOfBirth.Visible := not tmp;
     isValid := isValid and tmp;

     tmp := (CompareDate( dtpBirthDate.Date, Now) <> GreaterThanValue);
     epDateOfBirth.Visible := not tmp;
     isValid := isValid and tmp;

     Result := isValid;
end;


{$R *.dfm}

procedure TForm2.btnAddClick(Sender: TObject);
begin
     if ValidateForm then
     begin
       //TODO dodaj co trzeba
       OperativeBeingEdited^.FirstName := edtFirstName.Text;
       OperativeBeingEdited^.LastName := edtLastName.Text;
       OperativeBeingEdited^.NickName := edtNickName.Text;
       OperativeBeingEdited^.BirthPlace := edtPlaceOfBirth.Text;
       OperativeBeingEdited^.DateOfBirth := dtpBirthDate.DateTime;
       DialogResult := True;
       Close;

     end;
end;

procedure TForm2.btnCloseClick(Sender: TObject);
begin
     OperativeBeingEdited := nil;
     Close;
end;


procedure TForm2.FormCreate(Sender: TObject);
begin
     OperativeBeingEdited := nil;
     DialogResult := False;
end;

end.
