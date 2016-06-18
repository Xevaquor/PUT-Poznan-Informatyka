object Form2: TForm2
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Edytuj TW'
  ClientHeight = 189
  ClientWidth = 361
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 11
    Width = 20
    Height = 13
    Caption = 'Imi'#281
  end
  object Nazwisko: TLabel
    Left = 8
    Top = 38
    Width = 44
    Height = 13
    Caption = 'Nazwisko'
  end
  object Label3: TLabel
    Left = 8
    Top = 65
    Width = 51
    Height = 13
    Caption = 'Pseudonim'
  end
  object Label4: TLabel
    Left = 8
    Top = 93
    Width = 73
    Height = 13
    Caption = 'Data urodzenia'
  end
  object Label5: TLabel
    Left = 8
    Top = 123
    Width = 85
    Height = 13
    Caption = 'Miejsce urodzenia'
  end
  object epFirstName: TLabel
    Left = 240
    Top = 11
    Width = 93
    Height = 13
    Caption = 'Niew'#322'a'#347'ciwy format'
    Color = clRed
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    Visible = False
  end
  object epLastName: TLabel
    Left = 240
    Top = 38
    Width = 93
    Height = 13
    Caption = 'Niew'#322'a'#347'ciwy format'
    Color = clRed
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    Visible = False
  end
  object epNickName: TLabel
    Left = 240
    Top = 65
    Width = 93
    Height = 13
    Caption = 'Niew'#322'a'#347'ciwy format'
    Color = clRed
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    Visible = False
  end
  object epDateOfBirth: TLabel
    Left = 240
    Top = 93
    Width = 93
    Height = 13
    Caption = 'Niew'#322'a'#347'ciwy format'
    Color = clRed
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    Visible = False
  end
  object epPlaceOfBirth: TLabel
    Left = 240
    Top = 123
    Width = 93
    Height = 13
    Caption = 'Niew'#322'a'#347'ciwy format'
    Color = clRed
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    Visible = False
  end
  object edtFirstName: TEdit
    Left = 113
    Top = 8
    Width = 121
    Height = 21
    TabOrder = 0
  end
  object edtLastName: TEdit
    Left = 113
    Top = 35
    Width = 121
    Height = 21
    TabOrder = 1
  end
  object edtNickName: TEdit
    Left = 113
    Top = 62
    Width = 121
    Height = 21
    TabOrder = 2
  end
  object edtPlaceOfBirth: TEdit
    Left = 113
    Top = 120
    Width = 121
    Height = 21
    TabOrder = 4
  end
  object dtpBirthDate: TDateTimePicker
    Left = 113
    Top = 93
    Width = 121
    Height = 21
    Date = 41629.648061064810000000
    Time = 41629.648061064810000000
    TabOrder = 3
  end
  object btnAdd: TButton
    Left = 197
    Top = 150
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    TabOrder = 5
    OnClick = btnAddClick
  end
  object btnClose: TButton
    Left = 278
    Top = 150
    Width = 75
    Height = 25
    Caption = 'Zamknij okno'
    TabOrder = 6
    OnClick = btnCloseClick
  end
end
