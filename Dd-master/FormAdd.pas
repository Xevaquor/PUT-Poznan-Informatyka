unit FormAdd;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.ComCtrls,
  System.RegularExpressions, DateUtils, Types, TOperativeUnit, Vcl.ExtDlgs;

procedure Append(item : TElemType); stdcall
	external 'LinkedList.dll' name 'Append';

type
  TForm1 = class(TForm)
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
    btnAdd: TButton;
    btnClose: TButton;
    epFirstName: TLabel;
    epLastName: TLabel;
    epNickName: TLabel;
    epDateOfBirth: TLabel;
    epPlaceOfBirth: TLabel;
    procedure btnAddClick(Sender: TObject);
    procedure btnCloseClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
      private
    function ValidateForm : Boolean;
  public
    HasAdded : Bool;
  end;

var
  Form1: TForm1;

implementation

function TForm1.ValidateForm: Boolean;
var
isValid, tmp : Boolean;
namePattern : string;
regex : TRegEx;
begin
     isValid := True;
     namePattern := '^[a-zA-z\-\ Œ£êó³œ¹¿Ÿæñ]+$';
     regex.Create(namePattern);

     tmp := regex.IsMatch(edtFirstName.Text);
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

procedure TForm1.btnAddClick(Sender: TObject);
var
   entry : TOperative;
begin
     if ValidateForm then
     begin
       //TODO dodaj co trzeba
       entry.FirstName := edtFirstName.Text;
       entry.LastName := edtLastName.Text;
       entry.NickName := edtNickName.Text;
       entry.BirthPlace := edtPlaceOfBirth.Text;
       entry.DateOfBirth := dtpBirthDate.DateTime;

       Append(entry);

       edtFirstName.Text := '';
       edtLastName.Text := '';
       edtNickName.Text := '';
       edtPlaceOfBirth.Text := '';
       edtFirstName.SetFocus;

       HasAdded := true;
     end;
end;

procedure TForm1.btnCloseClick(Sender: TObject);
begin
     Close;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
     HasAdded := False;
end;

end.
