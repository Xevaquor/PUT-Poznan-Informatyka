program LinkedListTest;

{$APPTYPE CONSOLE}

uses
  SysUtils,
  TOperativeUnit in 'TOperativeUnit.pas';

procedure Append(item : TElemType); stdcall
	external 'LinkedList.dll' name 'Append';
procedure WriteEach; stdcall
	external 'LinkedList.dll' name 'WriteEach';
procedure Seed; stdcall
	external 'LinkedList.dll' name 'Seed';
procedure WriteToFile; stdcall
	external 'LinkedList.dll' name 'WriteToFile';
procedure ReadFromFile; stdcall
	external 'LinkedList.dll' name 'ReadFromFile';

var
	bolek, stokrotka : TOperative;
begin
	WriteEach;
	//ReadFromFile;
	WriteEach;
	Seed;
	WriteEach;
	WriteToFile;
end.
