object frmDirectSQL: TfrmDirectSQL
  Left = 270
  Top = 146
  Width = 617
  Height = 404
  Caption = 'Direct SQL'
  Color = clBtnFace
  Constraints.MinHeight = 350
  Constraints.MinWidth = 400
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  DesignSize = (
    601
    368)
  PixelsPerInch = 96
  TextHeight = 13
  object sgResp: TStringGrid
    Left = 0
    Top = 168
    Width = 608
    Height = 208
    Anchors = [akLeft, akTop, akRight, akBottom]
    ColCount = 10
    DefaultRowHeight = 16
    RowCount = 12
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goEditing]
    TabOrder = 2
    ColWidths = (
      18
      64
      64
      64
      64
      64
      64
      64
      64
      64)
    RowHeights = (
      16
      16
      16
      16
      16
      16
      16
      16
      16
      16
      16
      16)
  end
  object btnExecute: TButton
    Left = 6
    Top = 131
    Width = 75
    Height = 25
    Caption = 'GO >>'
    TabOrder = 0
    OnClick = btnExecuteClick
  end
  object btnClear: TButton
    Left = 112
    Top = 131
    Width = 75
    Height = 25
    Caption = 'Clear'
    TabOrder = 1
    OnClick = btnClearClick
  end
  object mmoQuery: TScintilla
    Left = 0
    Top = 0
    Width = 609
    Height = 124
    Color = clWhite
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = []
    Anchors = [akLeft, akTop, akRight]
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
    FoldMarkers.MarkerType = sciMarkCustom
    FoldMarkers.FoldOpen.BackColor = clDefault
    FoldMarkers.FoldOpen.ForeColor = clDefault
    FoldMarkers.FoldOpen.MarkerType = sciMArrowDown
    FoldMarkers.FoldClosed.BackColor = clDefault
    FoldMarkers.FoldClosed.ForeColor = clDefault
    FoldMarkers.FoldClosed.MarkerType = sciMArrow
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
