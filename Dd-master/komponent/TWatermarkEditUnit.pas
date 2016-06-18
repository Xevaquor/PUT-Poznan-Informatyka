unit TWatermarkEditUnit;

interface

uses
  Windows, Messages, System.SysUtils, System.Classes, Vcl.Controls, Vcl.StdCtrls, Vcl.Graphics;

type
  TWatermarkEdit = class(TEdit)
  private
    HandlingEvent : Boolean;
    procedure  CMFocusGain(var Message : TMessage); message WM_SETFOCUS;
    procedure  CMFocusLost(var Message : TMessage); message WM_KILLFOCUS;
  protected
    { Protected declarations }
  public
    IsEmpty : Boolean;
    Watermark : String;
    function GetValue : String;
    procedure Change; override;
    constructor Create(AOwner: TComponent); override;
    procedure Clear;
    procedure CallFocusLost;
  published
  end;

procedure Register;

implementation

procedure TWatermarkEdit.CallFocusLost;
var
  stub : TMessage;
begin
stub.Msg := WM_NULL;
  CMFocusLost(stub);
end;

procedure TWatermarkEdit.Clear;
var
  stub : TMessage;
begin
     stub.Msg := WM_NULL;
  IsEmpty := True;
  CMFocusLost(stub);
end;

procedure TWatermarkEdit.CMFocusGain(var Message: TMessage);
begin
    if IsEmpty then
    begin
      Font.Color := clBlack;
      HandlingEvent := True;
      Text := '';
      HandlingEvent := False;
    end;
    inherited;
end;
procedure TWatermarkEdit.CMFocusLost(var Message: TMessage);
begin
    if IsEmpty then
    begin
      Font.Color := clGray;
      HandlingEvent := True;
      Text := Watermark;
      HandlingEvent := False;
    end;
    inherited;
end;

constructor TWatermarkEdit.Create(AOwner: TComponent);
begin
     HandlingEvent := False;
     inherited Create(AOwner);
     IsEmpty := True;
     Watermark := 'watermark';
     Text := Watermark;
     Font.Color := clGray;
     end;

procedure TWatermarkEdit.Change;
begin
    if HandlingEvent then
       Exit;


    HandlingEvent := True;
    if Text = '' then
  begin
     IsEmpty := True;
  end
  else
  begin
       IsEmpty := False;
  end;


    inherited;
  HandlingEvent := False;
end;

function TWatermarkEdit.GetValue(): String;
begin
     if IsEmpty then
        Result := ''
     else
         Result := Text;
end;



procedure Register;
begin
  RegisterComponents('Samples', [TWatermarkEdit]);
end;

end.
