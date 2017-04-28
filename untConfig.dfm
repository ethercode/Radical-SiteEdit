object frmConfig: TfrmConfig
  Left = 295
  Top = 199
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'Radical SiteEdit - Connection Options'
  ClientHeight = 272
  ClientWidth = 404
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnCloseQuery = FormCloseQuery
  OnKeyDown = FormKeyDown
  DesignSize = (
    404
    272)
  PixelsPerInch = 96
  TextHeight = 13
  object grpConnection: TGroupBox
    Left = 8
    Top = 7
    Width = 387
    Height = 250
    Anchors = [akLeft, akRight, akBottom]
    Caption = 'Connection Options'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    DesignSize = (
      387
      250)
    object lblServer: TLabel
      Left = 7
      Top = 124
      Width = 127
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = 'MySQL Host:'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
    end
    object lblDatabase: TLabel
      Left = 7
      Top = 172
      Width = 127
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = 'MySQL Database:'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
    end
    object lblUsername: TLabel
      Left = 7
      Top = 148
      Width = 127
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = 'MySQL Username:'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
    end
    object lblSqlPipe: TLabel
      Left = 7
      Top = 196
      Width = 127
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = 'Port or Sql Pipe URL:'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
    end
    object Label1: TLabel
      Left = 7
      Top = 100
      Width = 127
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = 'Configuration Name:'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
    end
    object lblOK: TLabel
      Tag = 1
      Left = 230
      Top = 226
      Width = 148
      Height = 13
      Cursor = crHandPoint
      Alignment = taRightJustify
      Anchors = [akRight, akBottom]
      Caption = 'Accept connection options'
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsUnderline]
      ParentFont = False
      OnClick = lblOKClick
    end
    object lblCancel: TLabel
      Tag = 1
      Left = 9
      Top = 226
      Width = 104
      Height = 13
      Cursor = crHandPoint
      Anchors = [akRight, akBottom]
      Caption = 'Abandon Changes'
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsUnderline]
      ParentFont = False
      OnClick = lblCancelClick
    end
    object Label2: TLabel
      Left = 8
      Top = 67
      Width = 290
      Height = 13
      Caption = 'You cannot use: < > / \ ? * : | " in the name.'
    end
    object Label3: TLabel
      Left = 8
      Top = 24
      Width = 333
      Height = 13
      Caption = 'Enter the name, host, username, database and SQL'
    end
    object Label4: TLabel
      Left = 8
      Top = 40
      Width = 192
      Height = 13
      Caption = 'Pipe URL for your connection.'
    end
    object edtHost: TEdit
      Left = 138
      Top = 121
      Width = 240
      Height = 20
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
    object edtDatabase: TEdit
      Left = 138
      Top = 169
      Width = 240
      Height = 20
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object edtUsername: TEdit
      Left = 138
      Top = 145
      Width = 240
      Height = 20
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object edtSqlPipe: TEdit
      Left = 138
      Top = 193
      Width = 240
      Height = 20
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
    object edtName: TEdit
      Left = 138
      Top = 97
      Width = 240
      Height = 20
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnChange = edtNameChange
      OnKeyPress = edtNameKeyPress
    end
  end
end
