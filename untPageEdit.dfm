object frmPageEdit: TfrmPageEdit
  Left = 296
  Top = 110
  Width = 672
  Height = 564
  Caption = 'Title'
  Color = clBtnFace
  Constraints.MinHeight = 475
  Constraints.MinWidth = 513
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Verdana'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 656
    Height = 528
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      656
      528)
    object lblApply: TLabel
      Tag = 1
      Left = 615
      Top = 491
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
      Left = 519
      Top = 491
      Width = 21
      Height = 13
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
      Left = 558
      Top = 491
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
    object lblContentType_Static: TLabel
      Left = 4
      Top = 408
      Width = 79
      Height = 13
      Caption = 'Content type:'
    end
    object lblContentType: TLabel
      Left = 86
      Top = 408
      Width = 32
      Height = 13
      Caption = 'Type'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object grpBody: TGroupBox
      Left = 6
      Top = 3
      Width = 645
      Height = 339
      Anchors = [akLeft, akTop, akRight, akBottom]
      Caption = 'Body'
      TabOrder = 0
      DesignSize = (
        645
        339)
      object lblBinary: TLabel
        Tag = 1
        Left = 487
        Top = 319
        Width = 50
        Height = 13
        Cursor = crHandPoint
        Anchors = [akRight, akBottom]
        AutoSize = False
        Caption = 'Binary...'
        Font.Charset = ANSI_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Verdana'
        Font.Style = [fsUnderline]
        ParentFont = False
        OnClick = lblBinaryClick
      end
      object chkWordWrap: TCheckBox
        Left = 553
        Top = 318
        Width = 84
        Height = 17
        Cursor = crHandPoint
        TabStop = False
        Alignment = taLeftJustify
        Anchors = [akRight, akBottom]
        Caption = 'Word Wrap'
        Font.Charset = ANSI_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Verdana'
        Font.Style = [fsUnderline]
        ParentFont = False
        TabOrder = 0
        OnClick = chkWordWrapClick
      end
    end
    object grpAttributes: TGroupBox
      Left = 6
      Top = 346
      Width = 645
      Height = 142
      Anchors = [akLeft, akRight, akBottom]
      Caption = 'Attributes'
      TabOrder = 1
      DesignSize = (
        645
        142)
      object lblTitle: TLabel
        Left = 13
        Top = 18
        Width = 61
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Title:'
      end
      object lblDescription: TLabel
        Left = 3
        Top = 41
        Width = 71
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Description:'
      end
      object lblKeywords: TLabel
        Left = 13
        Top = 65
        Width = 61
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Keywords:'
      end
      object lblAltName: TLabel
        Left = 13
        Top = 89
        Width = 61
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Alt. Name:'
      end
      object lblDateTime: TLabel
        Left = 224
        Top = 90
        Width = 68
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Timestamp:'
      end
      object lblUpdate: TLabel
        Tag = 1
        Left = 441
        Top = 89
        Width = 44
        Height = 13
        Cursor = crHandPoint
        AutoSize = False
        Caption = 'Update'
        Font.Charset = ANSI_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Verdana'
        Font.Style = [fsUnderline]
        ParentFont = False
        OnClick = lblUpdateClick
      end
      object lblAccess: TLabel
        Left = 246
        Top = 115
        Width = 45
        Height = 14
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Access:'
      end
      object lblStyle: TLabel
        Left = 13
        Top = 113
        Width = 61
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Style:'
      end
      object edtTitle: TEdit
        Left = 78
        Top = 15
        Width = 559
        Height = 20
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnChange = edtTitleChange
        OnKeyDown = edtTitleKeyDown
      end
      object edtDescription: TEdit
        Left = 78
        Top = 38
        Width = 559
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnChange = edtDescriptionChange
        OnKeyDown = edtDescriptionKeyDown
      end
      object edtKeywords: TEdit
        Left = 78
        Top = 62
        Width = 559
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        OnChange = edtKeywordsChange
        OnKeyDown = edtKeywordsKeyDown
      end
      object edtAltName: TEdit
        Left = 78
        Top = 86
        Width = 139
        Height = 21
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        OnChange = edtAltNameChange
        OnKeyDown = edtAltNameKeyDown
      end
      object edtDateTime: TEdit
        Left = 296
        Top = 86
        Width = 138
        Height = 21
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        OnChange = edtDateTimeChange
        OnDblClick = edtDateTimeDblClick
        OnKeyDown = edtDateTimeKeyDown
      end
      object cbxAccess: TComboBox
        Left = 296
        Top = 112
        Width = 138
        Height = 21
        Style = csDropDownList
        Color = 15329769
        ItemHeight = 13
        TabOrder = 5
        OnChange = cbxAccessChange
        OnKeyDown = cbxAccessKeyDown
      end
      object cbxStyle: TComboBox
        Left = 78
        Top = 112
        Width = 139
        Height = 21
        Style = csDropDownList
        Color = 15329769
        ItemHeight = 13
        TabOrder = 6
        OnChange = edtStyleChange
        OnKeyDown = edtStyleKeyDown
      end
    end
    object stbMain: TStatusBar
      Left = 0
      Top = 509
      Width = 656
      Height = 19
      Panels = <>
      SimplePanel = True
    end
    object mmoBody: TScintilla
      Left = 17
      Top = 20
      Width = 623
      Height = 296
      Color = clWhite
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Lucida Console'
      Font.Style = []
      OnModified = mmoBodyModified
      OnKeyPress = mmoBodyKeyPress
      Anchors = [akLeft, akTop, akRight, akBottom]
      EOLStyle = eolCRLF
      Indentation = [KeepIndent, TabIndents, IndentationGuides]
      IndentWidth = 0
      MarginLeft = 1
      MarginRight = 1
      TabWidth = 4
      CodePage = cpAnsi
      Caret.ForeColor = clBlack
      Caret.LineBackColor = clYellow
      Caret.LineVisible = False
      Caret.Width = 3
      Caret.Period = 500
      Caret.LineBackAlpha = 256
      OtherOptions.ViewWSpace = sciWsInvisible
      OtherOptions.UsePalette = False
      OtherOptions.OverType = False
      OtherOptions.ViewEOL = False
      OtherOptions.EndAtLastLine = True
      OtherOptions.ScrollBarH = True
      OtherOptions.ScrollBarV = True
      OtherOptions.ScrollWidthTracking = False
      OtherOptions.PasteConvertEndings = True
      ActiveHotSpot.BackColor = clWhite
      ActiveHotSpot.ForeColor = clBlue
      ActiveHotSpot.Underlined = True
      ActiveHotSpot.SingleLine = True
      Colors.SelFore = 24576
      Colors.SelBack = 14342874
      Colors.MarkerFore = 10040115
      Colors.MarkerBack = clAqua
      Colors.FoldHi = clSilver
      Colors.FoldLo = clWhite
      Colors.WhiteSpaceFore = clBlack
      Colors.WhiteSpaceBack = clWhite
      Bookmark.BackColor = clDefault
      Bookmark.ForeColor = clDefault
      Bookmark.MarkerType = sciMCircle
      Gutter0.Width = 0
      Gutter0.MarginType = gutLineNumber
      Gutter0.Sensitive = False
      Gutter1.Width = 32
      Gutter1.MarginType = gutLineNumber
      Gutter1.Sensitive = True
      Gutter2.Width = 14
      Gutter2.MarginType = gutSymbol
      Gutter2.Sensitive = True
      Gutter3.Width = 0
      Gutter3.MarginType = gutSymbol
      Gutter3.Sensitive = False
      Gutter4.Width = 0
      Gutter4.MarginType = gutSymbol
      Gutter4.Sensitive = False
      WordWrapVisualFlags = []
      WordWrapVisualFlagsLocation = []
      LayoutCache = sciCacheCaret
      HideSelect = False
      WordWrap = sciNoWrap
      EdgeColumn = 200
      EdgeColor = clSilver
      WordChars = '_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'
      ControlCharSymbol = #0
      Folding = [foldFold, foldCompact, foldComment, foldPreprocessor, foldAtElse, foldHTML, foldHTMLPreProcessor]
      FoldMarkers.MarkerType = sciMarkPlusMinus
      FoldMarkers.FoldOpen.BackColor = clDefault
      FoldMarkers.FoldOpen.ForeColor = clDefault
      FoldMarkers.FoldOpen.MarkerType = sciMMinus
      FoldMarkers.FoldClosed.BackColor = clDefault
      FoldMarkers.FoldClosed.ForeColor = clDefault
      FoldMarkers.FoldClosed.MarkerType = sciMPlus
      FoldMarkers.FoldSub.BackColor = clDefault
      FoldMarkers.FoldSub.ForeColor = clDefault
      FoldMarkers.FoldSub.MarkerType = sciMEmpty
      FoldMarkers.FoldTail.BackColor = clDefault
      FoldMarkers.FoldTail.ForeColor = clDefault
      FoldMarkers.FoldTail.MarkerType = sciMEmpty
      FoldMarkers.FoldEnd.BackColor = clDefault
      FoldMarkers.FoldEnd.ForeColor = clDefault
      FoldMarkers.FoldEnd.MarkerType = sciMEmpty
      FoldMarkers.FoldOpenMid.BackColor = clDefault
      FoldMarkers.FoldOpenMid.ForeColor = clDefault
      FoldMarkers.FoldOpenMid.MarkerType = sciMEmpty
      FoldMarkers.FoldMidTail.BackColor = clDefault
      FoldMarkers.FoldMidTail.ForeColor = clDefault
      FoldMarkers.FoldMidTail.MarkerType = sciMEmpty
      FoldDrawFlags = [sciBelowIfNotExpanded]
      KeyCommands = <
        item
          Command = 2300
          ShortCut = 40
        end
        item
          Command = 2301
          ShortCut = 8232
        end
        item
          Command = 2342
          ShortCut = 16424
        end
        item
          Command = 2426
          ShortCut = 41000
        end
        item
          Command = 2302
          ShortCut = 38
        end
        item
          Command = 2303
          ShortCut = 8230
        end
        item
          Command = 2343
          ShortCut = 16422
        end
        item
          Command = 2427
          ShortCut = 40998
        end
        item
          Command = 2415
          ShortCut = 49190
        end
        item
          Command = 2416
          ShortCut = 57382
        end
        item
          Command = 2413
          ShortCut = 49192
        end
        item
          Command = 2414
          ShortCut = 57384
        end
        item
          Command = 2304
          ShortCut = 37
        end
        item
          Command = 2305
          ShortCut = 8229
        end
        item
          Command = 2308
          ShortCut = 16421
        end
        item
          Command = 2309
          ShortCut = 24613
        end
        item
          Command = 2428
          ShortCut = 40997
        end
        item
          Command = 2306
          ShortCut = 39
        end
        item
          Command = 2307
          ShortCut = 8231
        end
        item
          Command = 2310
          ShortCut = 16423
        end
        item
          Command = 2311
          ShortCut = 24615
        end
        item
          Command = 2429
          ShortCut = 40999
        end
        item
          Command = 2390
          ShortCut = 49189
        end
        item
          Command = 2391
          ShortCut = 57381
        end
        item
          Command = 2392
          ShortCut = 49191
        end
        item
          Command = 2393
          ShortCut = 57383
        end
        item
          Command = 2331
          ShortCut = 36
        end
        item
          Command = 2332
          ShortCut = 8228
        end
        item
          Command = 2431
          ShortCut = 40996
        end
        item
          Command = 2316
          ShortCut = 16420
        end
        item
          Command = 2317
          ShortCut = 24612
        end
        item
          Command = 2345
          ShortCut = 32804
        end
        item
          Command = 2314
          ShortCut = 35
        end
        item
          Command = 2315
          ShortCut = 8227
        end
        item
          Command = 2318
          ShortCut = 16419
        end
        item
          Command = 2319
          ShortCut = 24611
        end
        item
          Command = 2347
          ShortCut = 32803
        end
        item
          Command = 2432
          ShortCut = 40995
        end
        item
          Command = 2320
          ShortCut = 33
        end
        item
          Command = 2321
          ShortCut = 8225
        end
        item
          Command = 2433
          ShortCut = 40993
        end
        item
          Command = 2322
          ShortCut = 34
        end
        item
          Command = 2323
          ShortCut = 8226
        end
        item
          Command = 2434
          ShortCut = 40994
        end
        item
          Command = 2180
          ShortCut = 46
        end
        item
          Command = 2177
          ShortCut = 8238
        end
        item
          Command = 2336
          ShortCut = 16430
        end
        item
          Command = 2396
          ShortCut = 24622
        end
        item
          Command = 2324
          ShortCut = 45
        end
        item
          Command = 2179
          ShortCut = 8237
        end
        item
          Command = 2178
          ShortCut = 16429
        end
        item
          Command = 2325
          ShortCut = 27
        end
        item
          Command = 2326
          ShortCut = 8
        end
        item
          Command = 2326
          ShortCut = 8200
        end
        item
          Command = 2335
          ShortCut = 16392
        end
        item
          Command = 2176
          ShortCut = 32776
        end
        item
          Command = 2395
          ShortCut = 24584
        end
        item
          Command = 2176
          ShortCut = 16474
        end
        item
          Command = 2011
          ShortCut = 16473
        end
        item
          Command = 2177
          ShortCut = 16472
        end
        item
          Command = 2178
          ShortCut = 16451
        end
        item
          Command = 2179
          ShortCut = 16470
        end
        item
          Command = 2013
          ShortCut = 16449
        end
        item
          Command = 2327
          ShortCut = 9
        end
        item
          Command = 2328
          ShortCut = 8201
        end
        item
          Command = 2329
          ShortCut = 13
        end
        item
          Command = 2329
          ShortCut = 8205
        end
        item
          Command = 2333
          ShortCut = 16491
        end
        item
          Command = 2334
          ShortCut = 16493
        end
        item
          Command = 2373
          ShortCut = 16495
        end
        item
          Command = 2337
          ShortCut = 16460
        end
        item
          Command = 2338
          ShortCut = 24652
        end
        item
          Command = 2455
          ShortCut = 24660
        end
        item
          Command = 2339
          ShortCut = 16468
        end
        item
          Command = 2469
          ShortCut = 16452
        end
        item
          Command = 2340
          ShortCut = 16469
        end
        item
          Command = 2341
          ShortCut = 24661
        end>
      SelectedLanguage = 'null'
    end
  end
  object tmrIdle: TTimer
    Interval = 20000
    OnTimer = tmrIdleTimer
    Left = 24
    Top = 32
  end
  object opnBinary: TOpenDialog
    Options = [ofPathMustExist, ofFileMustExist, ofShareAware, ofEnableSizing, ofForceShowHidden]
    Left = 24
    Top = 72
  end
end
