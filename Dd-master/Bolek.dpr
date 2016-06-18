program Bolek;



{$R *.dres}

uses
  Forms,
  MainApplication in 'MainApplication.pas' {MainForm},
  FormAdd in 'FormAdd.pas' {Form1},
  FormEdit in 'FormEdit.pas' {Form2},
  Windows;

{$R *.res}

var
  Mutex : THandle;

begin
    Mutex := CreateMutex(nil, True, 'PLEASE_WORK_FOR_GOD_SAKE');
    if (mutex = 0) or (GetLastError = ERROR_ALREADY_EXISTS) then
    begin
         MessageBox(0, 'Ju¿ uruchomiono', ' ', MB_OK);
         Exit;
    end;

  Application.Initialize;
  Application.CreateForm(TMainForm, MainForm);
  Application.CreateForm(TForm1, Form1);
  Application.CreateForm(TForm2, Form2);
  Application.Run;
end.
