object frmMain: TfrmMain
  Left = 346
  Top = 200
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Title'
  ClientHeight = 408
  ClientWidth = 545
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Verdana'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  DesignSize = (
    545
    408)
  PixelsPerInch = 96
  TextHeight = 13
  object lblQuit: TLabel
    Tag = 1
    Left = 513
    Top = 370
    Width = 25
    Height = 14
    Cursor = crHandPoint
    Anchors = [akRight, akBottom]
    AutoSize = False
    Caption = 'Quit'
    Font.Charset = ANSI_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsUnderline]
    ParentFont = False
    OnClick = lblQuitClick
  end
  object Label1: TLabel
    Left = 8
    Top = 370
    Width = 191
    Height = 13
    Anchors = [akLeft, akBottom]
    Caption = '(c) 2008 Tamburlaine Murray'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object grpConnection: TGroupBox
    Left = 8
    Top = 8
    Width = 289
    Height = 172
    Caption = ' Connection '
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    DesignSize = (
      289
      172)
    object lblPassword: TLabel
      Left = 7
      Top = 87
      Width = 65
      Height = 13
      Alignment = taRightJustify
      Anchors = [akLeft, akBottom]
      AutoSize = False
      Caption = 'Password:'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
    end
    object lblConnect: TLabel
      Tag = 1
      Left = 232
      Top = 147
      Width = 47
      Height = 13
      Cursor = crHandPoint
      Alignment = taRightJustify
      Anchors = [akRight, akBottom]
      Caption = 'Connect'
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsUnderline]
      ParentFont = False
      OnClick = lblConnectClick
    end
    object Label2: TLabel
      Left = 7
      Top = 53
      Width = 65
      Height = 13
      Alignment = taRightJustify
      Anchors = [akLeft, akBottom]
      AutoSize = False
      Caption = 'Server:'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
    end
    object lblConnNew: TLabel
      Tag = 1
      Left = 8
      Top = 115
      Width = 131
      Height = 13
      Cursor = crHandPoint
      Anchors = [akRight, akBottom]
      Caption = 'Create new connection'
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsUnderline]
      ParentFont = False
      OnClick = lblConnNewClick
    end
    object lblConnModify: TLabel
      Tag = 1
      Left = 8
      Top = 131
      Width = 147
      Height = 13
      Cursor = crHandPoint
      Anchors = [akRight, akBottom]
      Caption = 'Modify current connection'
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsUnderline]
      ParentFont = False
      OnClick = lblConnModifyClick
    end
    object lblConnDelete: TLabel
      Tag = 1
      Left = 8
      Top = 147
      Width = 147
      Height = 13
      Cursor = crHandPoint
      Anchors = [akRight, akBottom]
      Caption = 'Delete current connection'
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsUnderline]
      ParentFont = False
      OnClick = lblConnDeleteClick
    end
    object lblComment1: TLabel
      Left = 8
      Top = 24
      Width = 251
      Height = 13
      Caption = 'Select the connection you want to use:'
    end
    object edtPassword: TEdit
      Left = 77
      Top = 84
      Width = 148
      Height = 20
      Anchors = [akLeft, akRight, akBottom]
      AutoSize = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      PasswordChar = '*'
      TabOrder = 1
      OnChange = edtPasswordChange
      OnKeyDown = OnServerKeyDown
    end
    object chkSavePassword: TCheckBox
      Left = 232
      Top = 86
      Width = 47
      Height = 17
      Cursor = crHandPoint
      Anchors = [akRight, akBottom]
      Caption = 'Save'
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsUnderline]
      ParentFont = False
      TabOrder = 2
      OnClick = chkSavePasswordClick
    end
    object cbxConfigurations: TComboBox
      Left = 77
      Top = 51
      Width = 204
      Height = 21
      Style = csDropDownList
      Anchors = [akLeft, akBottom]
      DropDownCount = 16
      ItemHeight = 13
      TabOrder = 0
      OnSelect = cbxConfigurationsSelect
    end
    object chkIEProxy: TCheckBox
      Left = 173
      Top = 113
      Width = 106
      Height = 17
      Cursor = crHandPoint
      Alignment = taLeftJustify
      Anchors = [akLeft, akBottom]
      Caption = 'IE Proxy Mode'
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsUnderline]
      ParentFont = False
      TabOrder = 3
    end
  end
  object grpPage: TGroupBox
    Left = 304
    Top = 8
    Width = 232
    Height = 354
    Anchors = [akLeft, akTop, akBottom]
    Caption = ' Content Pages '
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    DesignSize = (
      232
      354)
    object lblPageCreateNew: TLabel
      Tag = 1
      Left = 8
      Top = 281
      Width = 93
      Height = 14
      Cursor = crHandPoint
      Anchors = [akLeft, akBottom]
      AutoSize = False
      Caption = 'Create New ...'
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      OnClick = lblPageCreateNewClick
    end
    object lblPageEdit: TLabel
      Tag = 1
      Left = 120
      Top = 281
      Width = 43
      Height = 14
      Cursor = crHandPoint
      Anchors = [akLeft, akBottom]
      AutoSize = False
      Caption = 'Edit ...'
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      OnClick = lblPageEditClick
    end
    object lblPageDelete: TLabel
      Tag = 1
      Left = 120
      Top = 305
      Width = 43
      Height = 14
      Cursor = crHandPoint
      Anchors = [akLeft, akBottom]
      AutoSize = False
      Caption = 'Delete'
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      OnClick = lblPageDeleteClick
    end
    object lblPageRefresh: TLabel
      Tag = 1
      Left = 8
      Top = 305
      Width = 54
      Height = 14
      Cursor = crHandPoint
      Anchors = [akLeft, akBottom]
      AutoSize = False
      Caption = 'Refresh'
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      OnClick = lblPageRefreshClick
    end
    object lblEditing_Static: TLabel
      Left = 8
      Top = 50
      Width = 43
      Height = 13
      Caption = 'Editing:'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
    end
    object lblEditing: TLabel
      Left = 54
      Top = 50
      Width = 164
      Height = 13
      AutoSize = False
      Caption = 'None'
    end
    object lblComment3: TLabel
      Left = 8
      Top = 24
      Width = 191
      Height = 13
      Caption = 'Select a content page to edit:'
      Enabled = False
    end
    object lbxPages: TListBox
      Left = 8
      Top = 72
      Width = 212
      Height = 202
      TabStop = False
      Anchors = [akLeft, akTop, akRight, akBottom]
      Color = 15329769
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ItemHeight = 13
      ParentFont = False
      ScrollWidth = 400
      TabOrder = 0
      OnClick = lbxPagesClick
      OnDblClick = lbxPagesDblClick
    end
    object chkReverse: TCheckBox
      Left = 8
      Top = 329
      Width = 161
      Height = 17
      Cursor = crHandPoint
      Anchors = [akLeft, akBottom]
      Caption = 'Display newest first'
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = chkReverseClick
    end
  end
  object grpMaintainance: TGroupBox
    Left = 8
    Top = 320
    Width = 289
    Height = 42
    Anchors = [akLeft, akBottom]
    Caption = ' Maintainance '
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    object lblEditMenu: TLabel
      Tag = 1
      Left = 8
      Top = 18
      Width = 93
      Height = 14
      Cursor = crHandPoint
      AutoSize = False
      Caption = 'Edit menu'
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      OnClick = lblEditMenuClick
    end
    object lblDirectSQL: TLabel
      Tag = 1
      Left = 81
      Top = 18
      Width = 105
      Height = 14
      Cursor = crHandPoint
      AutoSize = False
      Caption = 'Direct SQL Query'
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      OnClick = lblDirectSQLClick
    end
    object lblUpdateTables: TLabel
      Tag = 1
      Left = 200
      Top = 18
      Width = 87
      Height = 14
      Cursor = crHandPoint
      AutoSize = False
      Caption = 'Update Tables'
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      OnClick = lblUpdateTablesClick
    end
  end
  object grpType: TGroupBox
    Left = 8
    Top = 186
    Width = 289
    Height = 128
    Anchors = [akLeft, akBottom]
    Caption = ' Content Types '
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    DesignSize = (
      289
      128)
    object lblType: TLabel
      Left = 8
      Top = 50
      Width = 33
      Height = 13
      Caption = 'Type:'
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
    end
    object lblTypeCreateNew: TLabel
      Tag = 1
      Left = 8
      Top = 79
      Width = 113
      Height = 14
      Cursor = crHandPoint
      AutoSize = False
      Caption = 'Create new type'
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      OnClick = lblTypeCreateNewClick
    end
    object lblTypeRename: TLabel
      Tag = 1
      Left = 141
      Top = 79
      Width = 135
      Height = 14
      Cursor = crHandPoint
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = 'Rename selected type'
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      OnClick = lblTypeRenameClick
    end
    object lblTypeDelete: TLabel
      Tag = 1
      Left = 141
      Top = 103
      Width = 140
      Height = 14
      Cursor = crHandPoint
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = 'Delete selected type'
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      OnClick = lblTypeDeleteClick
    end
    object lblTypeRefresh: TLabel
      Tag = 1
      Left = 8
      Top = 103
      Width = 68
      Height = 14
      Cursor = crHandPoint
      AutoSize = False
      Caption = 'Refresh list'
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      OnClick = lblTypeRefreshClick
    end
    object lblComment2: TLabel
      Left = 8
      Top = 20
      Width = 201
      Height = 13
      Caption = 'Select the content type to edit:'
      Enabled = False
    end
    object cbxContentTypes: TComboBox
      Left = 44
      Top = 46
      Width = 234
      Height = 21
      BevelInner = bvNone
      BevelOuter = bvNone
      Style = csDropDownList
      Anchors = [akLeft, akTop, akRight]
      Color = 15329769
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ItemHeight = 13
      ParentFont = False
      Sorted = True
      TabOrder = 0
      OnChange = cbxContentTypesChange
    end
  end
  object stbMain: TStatusBar
    Left = 0
    Top = 389
    Width = 545
    Height = 19
    Panels = <>
    SimplePanel = True
  end
  object tmrIdle: TTimer
    Interval = 20000
    OnTimer = tmrIdleTimer
    Left = 320
    Top = 85
  end
end
