object frmMenuEdit: TfrmMenuEdit
  Left = 363
  Top = 278
  Width = 447
  Height = 289
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'Title'
  Color = clBtnFace
  Constraints.MaxWidth = 600
  Constraints.MinHeight = 289
  Constraints.MinWidth = 422
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Verdana'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  DesignSize = (
    439
    262)
  PixelsPerInch = 96
  TextHeight = 13
  object grpMenuItems: TGroupBox
    Left = 8
    Top = 8
    Width = 185
    Height = 228
    Anchors = [akLeft, akTop, akBottom]
    Caption = 'Menu Items'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    DesignSize = (
      185
      228)
    object lblNew: TLabel
      Tag = 1
      Left = 8
      Top = 181
      Width = 49
      Height = 13
      Cursor = crHandPoint
      Anchors = [akRight, akBottom]
      AutoSize = False
      Caption = 'New'
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsUnderline]
      ParentFont = False
      OnClick = lblNewClick
      OnDblClick = lblNewClick
    end
    object lblDelete: TLabel
      Tag = 1
      Left = 8
      Top = 205
      Width = 49
      Height = 13
      Cursor = crHandPoint
      Anchors = [akRight, akBottom]
      AutoSize = False
      Caption = 'Delete'
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsUnderline]
      ParentFont = False
      OnClick = lblDeleteClick
      OnDblClick = lblDeleteClick
    end
    object lblMoveUp: TLabel
      Tag = 1
      Left = 88
      Top = 181
      Width = 65
      Height = 13
      Cursor = crHandPoint
      Anchors = [akRight, akBottom]
      AutoSize = False
      Caption = 'Move up'
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsUnderline]
      ParentFont = False
      OnClick = lblMoveUpClick
      OnDblClick = lblMoveUpClick
    end
    object lblMoveDown: TLabel
      Tag = 1
      Left = 88
      Top = 205
      Width = 73
      Height = 13
      Cursor = crHandPoint
      Anchors = [akRight, akBottom]
      AutoSize = False
      Caption = 'Move down'
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsUnderline]
      ParentFont = False
      OnClick = lblMoveDownClick
      OnDblClick = lblMoveDownClick
    end
    object lbxItems: TListBox
      Left = 8
      Top = 16
      Width = 169
      Height = 158
      Anchors = [akLeft, akTop, akRight, akBottom]
      ItemHeight = 13
      MultiSelect = True
      TabOrder = 0
      OnClick = lbxItemsClick
      OnKeyDown = lbxItemsKeyDown
    end
  end
  object grpProperties: TGroupBox
    Left = 200
    Top = 8
    Width = 232
    Height = 177
    Anchors = [akLeft, akTop, akRight]
    Caption = 'Properties'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    DesignSize = (
      232
      177)
    object lblText: TLabel
      Left = 8
      Top = 24
      Width = 48
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = 'Text:'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
    end
    object lblURL: TLabel
      Left = 8
      Top = 56
      Width = 48
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = 'URL:'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
    end
    object lblStyle: TLabel
      Left = 8
      Top = 88
      Width = 48
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = 'Style:'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
    end
    object lblAccess: TLabel
      Left = 8
      Top = 120
      Width = 48
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = 'Access:'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
    end
    object lblPropCancel: TLabel
      Tag = 1
      Left = 127
      Top = 154
      Width = 45
      Height = 13
      Cursor = crHandPoint
      Anchors = [akRight, akBottom]
      AutoSize = False
      Caption = 'Cancel'
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsUnderline]
      ParentFont = False
      OnClick = lblPropCancelClick
    end
    object lblPropApply: TLabel
      Tag = 1
      Left = 184
      Top = 154
      Width = 37
      Height = 13
      Cursor = crHandPoint
      Anchors = [akRight, akBottom]
      AutoSize = False
      Caption = 'Apply'
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      OnClick = lblPropApplyClick
    end
    object edtText: TEdit
      Left = 59
      Top = 21
      Width = 159
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
      OnChange = edtTextChange
    end
    object edtURL: TEdit
      Left = 59
      Top = 53
      Width = 159
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
      OnChange = edtURLChange
    end
    object cbxAccess: TComboBox
      Left = 59
      Top = 116
      Width = 158
      Height = 21
      Style = csDropDownList
      Color = 15329769
      ItemHeight = 13
      TabOrder = 2
      OnChange = cbxAccessChange
    end
    object cbxStyle: TComboBox
      Left = 59
      Top = 84
      Width = 158
      Height = 21
      Style = csDropDownList
      Color = 15329769
      ItemHeight = 13
      TabOrder = 3
      OnChange = cbxStyleChange
    end
  end
  object grpOptions: TGroupBox
    Left = 274
    Top = 195
    Width = 158
    Height = 41
    Anchors = [akRight, akBottom]
    Caption = 'Options'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    DesignSize = (
      158
      41)
    object lblApply: TLabel
      Tag = 1
      Left = 112
      Top = 18
      Width = 37
      Height = 13
      Cursor = crHandPoint
      Anchors = [akRight, akBottom]
      AutoSize = False
      Caption = 'Apply'
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      OnClick = lblApplyClick
    end
    object lblOK: TLabel
      Tag = 1
      Left = 16
      Top = 18
      Width = 20
      Height = 15
      Cursor = crHandPoint
      Anchors = [akRight, akBottom]
      AutoSize = False
      Caption = 'OK'
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
      Left = 55
      Top = 18
      Width = 45
      Height = 13
      Cursor = crHandPoint
      Anchors = [akRight, akBottom]
      AutoSize = False
      Caption = 'Cancel'
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsUnderline]
      ParentFont = False
      OnClick = lblCancelClick
    end
  end
  object stbMain: TStatusBar
    Left = 0
    Top = 243
    Width = 439
    Height = 19
    Panels = <>
    SimplePanel = True
  end
  object tmrIdle: TTimer
    Interval = 20000
    OnTimer = tmrIdleTimer
    Left = 24
    Top = 32
  end
end
