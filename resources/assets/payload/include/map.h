//
//  map.h
//  mt
//
//  Created by yinjianpeng on 2021/4/19.
//

#ifndef MAP_H
#define MAP_H

#include <cstdint>
#include <functional>
#ifdef _WINDOWS
#include <memory>
#include <vector>
#endif

#if __ANDROID__
  #if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
  #define RENDER_API __attribute__((visibility("default")))
  #else
  #define RENDER_API
  #endif
#else 
  #define RENDER_API
#endif

namespace mdgl {

enum ErrorType_ : int32_t { ErrorType_None = 0, ErrorType_InvalidPara, ErrorType_InnerError };

// constants for dynamic map
constexpr const char* DYNAMIC_MAP_KEY_STATE = "state";
constexpr const char* DYNAMIC_MAP_STATE_NORMAL = "normal";
constexpr const char* DYNAMIC_MAP_STATE_SELECTED = "selecting";

// constants for indoor
constexpr const char* INDOOR_OVERVIEW = "overview";

// flags for IMap()
enum FileSourceTypeFlag_ : int32_t {
  FileSourceTypeFlag_None,
  FileSourceTypeFlag_DefaultFileSource,
  FileSourceTypeFlag_LocalFileSource,
  FileSourceTypeFlag_OnlineFileSource
};

// flags for IMap()
enum MapModeFlag_ : int32_t {
  MapModeFlag_Continuous,  // continually updating map
  MapModeFlag_Still,       // a once-off still image
  MapModeFlag_Tile,
  MapModeFlag_Static,
};

// flags for setCameraOptionsRange()
enum CameraOptionsRangeFlag_ : int32_t {
  CameraOptionsRangeFlag_MaxZoom = 0,  // (zoom level)
  CameraOptionsRangeFlag_MinZoom,      // (zoom level)
  CameraOptionsRangeFlag_MaxPitch,     // (pitch angle)
  CameraOptionsRangeFlag_MinPitch,     // (pitch angle)
  CameraOptionsRangeFlag_CenterBounds  // (sw latitude, sw longitude, ne latitude, ne longitude)
};

// flags for setLayerOrder()
enum LayerOrderType_ : int32_t {
  LayerOrderType_Auto = 0,
  LayerOrderType_Order2D = 1,
  LayerOrderType_Order3D = 100,
  LayerOrderType_OrderSymbol = 200
};

// flags for setOverlayLayerOrder()
enum OverlayLayerOrderType_ : int32_t {
  OverlayLayerOrderType_SymbolUnder = 0,
  OverlayLayerOrderType_SymbolAbove = 1
};

// flags for setTrafficColor()
enum TrafficLevel_ : int32_t {
  TrafficLevel_Smooth = 0,
  TrafficLevel_Slow,
  TrafficLevel_Congested,
  TrafficLevel_SeriousCongested
};

// flags for IMap()
enum RenderFuncSwitch_ : int32_t {
  RenderFuncSwitch_None = 0,
  RenderFuncSwitch_NewSymbol = 1,
  RenderFuncSwitch_NewSymbolTile = 2,
  RenderFuncSwitch_PreloadTile = 4,
  RenderFuncSwitch_NewSymbolAlongLine = 8,
  RenderFuncSwitch_NewSymbolAlongLineTile = 16,
  RenderFuncSwitch_UseUBOIfSupport = 32
};

// flags for setGeojsonSourceThreadMode()
enum ThreadModeFlag_ : int32_t { ThreadMode_MultiThread = 0, ThreadMode_CustomThread, ThreadMode_RenderThread };

// flags for Raster Internal or Foreign
enum RasterStateFlag_ : int32_t { Raster_Internal = 0, Raster_Foreign, Raster_MT, Raster_Mapbox, Raster_Mix };

enum StyleLoadingFlag_ : int32_t {StyleLoadingFlag_None = 0, StyleLoadingFlag_Cache, StyleLoadingFlag_Network, StyleLoadingFlag_Local};

/// @{ layer properties enum
// for data dirven of enum type, you need to wirte the enum name such as "{round}","{butt}", you can se the enum name in
// comments
enum LineCapType_ : int32_t {
  LineCapType_Round,   // round
  LineCapType_Butt,    // butt
  LineCapType_Square,  // square
};

enum LineJoinType_ : int32_t {
  LineJoinType_Miter,  // miter
  LineJoinType_Bevel,  // bevel
  LineJoinType_Round,  // round
};

enum UnitType_ : int32_t {
  UnitType_Meter,  // meter
  UnitType_Pixel   // px
};

enum AnchorType_ : int32_t {
  AnchorType_Map,      // map
  AnchorType_Viewport  // viewport
};

enum AlignmentType_ : int32_t {
  AlignmentType_Map,       // map
  AlignmentType_Viewport,  // viewport
  AlignmentType_Auto       // auto
};

enum SymbolPlacementType_ : int32_t {
  SymbolPlacementType_Point,  // point
  SymbolPlacementType_Line,   // line
  SymbolPlacementType_Fill    // fill
};

enum TextJustifyType_ : int32_t {
  TextJustifyType_Center,  // center
  TextJustifyType_Left,    // left
  TextJustifyType_Right,   // right
  TextJustifyType_Icon     // icon
};

enum SymbolAnchorType_ : int32_t {
  SymbolAnchorType_Center,          // center
  SymbolAnchorType_Left,            // left
  SymbolAnchorType_Right,           // right
  SymbolAnchorType_Top,             // top
  SymbolAnchorType_Bottom,          // bottom
  SymbolAnchorType_TopLeft,         // top-left
  SymbolAnchorType_TopRight,        // top-right
  SymbolAnchorType_BottomLeft,      // bottom-left
  SymbolAnchorType_BottomRight,     // bottom-right
  SymbolAnchorType_Custom,          // custom
  SymbolAnchorType_AroundIcon,      // around-icon
  SymbolAnchorType_AroundIconNTop,  // around-icon-ntop
};

enum IconTextFitType_ : int32_t {
  IconTextFitType_None,   // none
  IconTextFitType_Both,   // both
  IconTextFitType_Width,  // width
  IconTextFitType_Height  // height
};

enum FillEffectType_ : int32_t {
  FillEffectType_None,      // none
  FillEffectType_WaterWave  // water-wave
};

enum HeatMapRenderType_ : int32_t {
  HeatMapRenderType_Circle,  // circle
  HeatMapRenderType_Square,  // square
  HeatMapRenderType_Hexagon  // hexagon
};

enum GradientType_ : int32_t {
  GradientType_Interval,  // interval
  GradientType_Linear     // linear
};

enum TileCacheType_ : int32_t {
  TileCacheType_NoCache,     // tile cache size is 0
  TileCacheType_QualityLow,  // tile cache size is auto calculated
};

enum WeatherType_ : int32_t {
  WeatherType_Hot,            // 高温(太阳和扭曲)
  WeatherType_Hot_Distortion, // 仅高温扭曲
  WeatherType_Hot_Sun,        // 仅高温太阳
  WeatherType_Rain_Medium,    // 小中雨
  WeatherType_Rain_Large,     // 大雨
  WeatherType_Rain_Storm,     // 暴雨
  WeatherType_Snow_Medium,    // 小中雪
  WeatherType_Snow_Large,     // 大雪
  WeatherType_Snow_Storm,     // 暴雪
  WeatherType_Dust,           // 沙尘
};

// Graphics Driver Type
// This type corresponds to the definition of Engine's RenderEnum
enum RenderBackendType_ : uint8_t {
  RenderBackendType_OpenGL = 2,
  RenderBackendType_Metal = 3, // just valid for ios
};

enum BasemapSourceTypeFlagFlag_ : int32_t {
  BasemapSourceTypeFlag_Vector,         // vector source & tile, enable apply style
  BasemapSourceTypeFlag_Raster          // raster source
};
/// @}

enum TilesetScheme_ : bool { XYZ, TMS };

enum AntiAliasingTypeFlag_ : uint32_t {
  AntiAliasingTypeFlag_None = 0,      // 无抗锯齿
  AntiAliasingTypeFlag_MetalMSAA = 1 << 0  // Metal MSAA
};

// flags for setLayerProperty(), setLayerPropertyByDataDriven()
enum LayerPropertyFlag_ : int32_t {
  // Fill
  /**
   * @brief The opacity of the entire fill layer.
   * @data-driven y
   * @layout yes when it's data-driven express("{***}"), or not.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @parameters opatity, range:[0,1]
   * @default 1.0
   */
  LayerPropertyFlag_FillOpacity = 1000,

  /**
   * @brief The color of the filled part of this layer. This color can be specified as rgba with an alpha component.
   * @data-driven y
   * @layout yes when it's data-driven express("{***}"), or not.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @parameters {r,g,b,a}, range:[0,1]
   * @default "#000000"
   */
  LayerPropertyFlag_FillColor,

  /**
   * @brief The geometry's offset in pixel. Values are [x, y] where negatives indicate left and up, respectively.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @parameters {tranxlateX, translateY}
   * @default {0, 0}
   */
  //  LayerPropertyFlag_FillTranslate,

  /**
   * @brief Controls the frame of reference for fill-translate.
   * enum "map": The fill is translated relative to the map.
   * enum "viewport": The fill is translated relative to the viewport.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, const char*)
   * @parameters AnchorType_
   * @default "map"
   */
  //  LayerPropertyFlag_FillTranslateAnchor,

  /**
   * @brief Name of image to use for drawing image fills. For seamless patterns, image width and height must be a factor
   * of two (2, 4, 8, ..., 512).
   * @data-driven y
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, const char*, const char*)
   * @default ""
   */
  LayerPropertyFlag_FillImage,

  /**
   * @brief The height of the entire fill layer.
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @default 0.0
   */
  LayerPropertyFlag_FillHeight,

  /**
   * @brief Sorts features in ascending order based on this value. Features with a higher sort key will appear above
   * features with a lower sort key.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, const char*, const char*)
   * @default ""
   */
  LayerPropertyFlag_FillSortKey,

  // Fill-Extrusion
  /**
   * @brief The opacity of the entire fill-extrusion layer.
   * @data-driven y
   * @layout yes when it's data-driven express("{***}"), or not.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @parameters opatity, range:[0,1]
   * @default 1.0
   */
  LayerPropertyFlag_ExtrusionOpacity = 2000,

  /**
   * @brief The color of the fill-extrusion part of this layer. This color can be specified as rgba with an alpha
   * component.
   * @data-driven y
   * @layout yes when it's data-driven express("{***}"), or not.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @parameters {r,g,b,a}, range:[0,1]
   * @default "#000000"
   */
  LayerPropertyFlag_ExtrusionColor,

  /**
   * @brief Name of image to use for drawing image fill-extrusion. For seamless patterns, image width and height must be
   * a factor of two (2, 4, 8, ..., 512).
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, const char*, const char*)
   * @default ""
   */
  LayerPropertyFlag_ExtrusionPattern,

  /**
   * @brief The ratio of padding in horizontal direction to the total length of padding and pattern width.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @default 0.0f
   */
  LayerPropertyFlag_ExtrusionLRPaddingRatio,

  /**
   * @brief The ratio of padding in vertical direction to the total length of padding and pattern height.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @default 0.0f
   */
  LayerPropertyFlag_ExtrusionTBPaddingRatio,

  /**
   * @brief The Minimum camera pitch when to extrusion this layer.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @default 10.0f
   */
  LayerPropertyFlag_ExtrusionMinPitch,

  /**
   * @brief The height with which to extrusion this layer.
   * @data-driven y
   * @layout y when it's data-driven express("{***}"), or n.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @default 0.0f
   */
  LayerPropertyFlag_ExtrusionHeight,

  /**
   * @brief The Unit of the height and the base of fill extrusion.
   * enum "meter": Unit in meters.
   * enum "pixel": Unit in pixels.
   * @data-driven n
   * @layout dependent on fill extrusion height and base.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, const char*)
   * @parameters UnitType_
   * @default "meter"
   */
  LayerPropertyFlag_ExtrusionHeightUnit,

  /**
   * @brief The height with which to extrude the base of this layer. Must be less than or equal to
   * fill-extrusion-height.
   * @data-driven y
   * @layout y when it's data-driven express("{***}"), or n.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @default 0.0f
   */
  LayerPropertyFlag_ExtrusionBase,

  /**
   * @brief The outline color of outline of fill extrusion.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @parameters {r,g,b,a}, range:[0,1]
   * @default {}
   */
  LayerPropertyFlag_ExtrusionOutlineColor,

  /**
   * @brief The color of top surface of fill extrusion.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @parameters {r,g,b,a}, range:[0,1]
   * @default {}
   */
  LayerPropertyFlag_ExtrusionTopSurfaceColor,

  /**
   * @brief hide the top surface of fill extrusion.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, bool, const char*)
   * @default false
   */
  LayerPropertyFlag_ExtrusionHideTopSurface,

  /**
   * @brief Sorts features in ascending order based on this value. Features with a higher sort key will appear above
   * features with a lower sort key.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, const char*,  const char*)
   * @default ""
   */
  LayerPropertyFlag_ExtrusionSortKey,

  /**
   * @brief The outline width of fill extrusion.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @parameters {r,g,b,a}, range:more than 0
   * @default {}
   */
  LayerPropertyFlag_ExtrusionOutlineWidth,

  /**
   * @brief Vertex indices of fill extrusion that enable to render outline.
   * @data-driven n
   * @layout n
   * @default ""
   */
  LayerPropertyFlag_ExtrusionOutlineVertexIndices,

  // Line
  /**
   * @brief The display of line endings.
   * enum "butt": A cap with a squared-off end which is drawn to the exact endpoint of the line.
   * enum "round": A cap with a rounded end which is drawn beyond the endpoint of the line at a radius of one-half of
   * the line's width and centered on the endpoint of the line. enum "square": A cap with a squared-off end which is
   * drawn beyond the endpoint of the line at a distance of one-half of the line's width.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, const char*)
   * @parameters LineCapType_
   * @default "round"
   */
  LayerPropertyFlag_LineCap = 3000,

  /**
   * @brief The display of lines when joining.
   * enum "bevel": A join with a squared-off end which is drawn beyond the endpoint of the line at a distance of
   * one-half of the line's width. enum "round": A join with a rounded end which is drawn beyond the endpoint of the
   * line at a radius of one-half of the line's width and centered on the endpoint of the line. enum "miter": A join
   * with a sharp, angled corner which is drawn with the outer sides beyond the endpoint of the path until they meet.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, const char*)
   * @parameters LineJoinType_
   * @default "round"
   */
  LayerPropertyFlag_LineJoin,

  /**
   * @brief The opacity at which the line will be drawn.
   * @data-driven y
   * @layout yes when it's data-driven express("{***}"), or not.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @parameters opatity, range:[0,1]
   * @default 1.0
   */
  LayerPropertyFlag_LineOpacity,

  /**
   * @brief The color with which the line will be drawn.
   * @data-driven y
   * @layout yes when it's data-driven express("{***}"), or not.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @parameters {r,g,b,a}, range:[0,1]
   * @default "#000000"
   */
  LayerPropertyFlag_LineColor,

  /**
   * @brief The height at which the line will be drawn. Units in meters.
   * @data-driven y
   * @layout yes when it's data-driven express("{***}"), or not.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @default 0.0f
   */
  LayerPropertyFlag_LineHeight,

  /**
   * @brief the unit of line width
   * @data-driven y
   * @layout yes when it's data-driven express("{***}"), or not.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, const char*)
   * @parameters UnitType_
   * @default Pixel
   */
  LayerPropertyFlag_LineWidthUnit,

  /**
   * @brief Stroke thickness.
   * @data-driven y
   * @layout yes when it's data-driven express("{***}"), or not.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @default 1.0f
   */
  LayerPropertyFlag_LineWidth,

  /**
   * @brief The line's offset. For linear features, a positive value offsets the line to the right, relative to the
   * direction of the line, and a negative value to the left. For polygon features, a positive value results in an
   * inset, and a negative value results in an outset.
   * @data-driven y
   * @layout yes when it's data-driven express("{***}"), or not.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @default 0.0f
   */
  LayerPropertyFlag_LineOffset,

  /**
   * @brief Blur applied to the line, in pixels.
   * @data-driven y
   * @layout yes when it's data-driven express("{***}"), or not.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @default 0.0f
   */
  LayerPropertyFlag_LineBlur,

  /**
   * @brief Specifies the lengths of the alternating dashes and gaps that form the dash pattern. The lengths are later
   * scaled by the line width. To convert a dash length to pixels, multiply the length by the current line width. Note
   * that GeoJSON sources with lineMetrics: true specified won't render dashed lines to the expected scale. Units in
   * line widths. Disabled by line-pattern.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @default {}
   */
  LayerPropertyFlag_LineDasharray,

  /**
   * @brief Name of image in sprite to use for drawing image lines. For seamless patterns, image width must be a factor
   * of two (2, 4, 8, ..., 512).
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, const char*,  const char*)
   * @default ''
   */
  LayerPropertyFlag_LinePattern,

  /**
   * @brief The gap width of image. Units in pixels.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float,  const char*)
   * @default 0.0f
   */
  LayerPropertyFlag_LinePatternSpacing,

  /**
   * @brief Defines a gradient with which to color a line feature. Can only be used with GeoJSON sources that specify
   * "lineMetrics": true.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @parameters {key1,r1,g1,b1,a1,key2,r2,g2,b2,a2...}
   * @default {}
   */
  LayerPropertyFlag_LineGradientColor,

  /**
   * @brief The interpolation type of gradient color. Produces continuous, smooth or interval results by interpolating
   * between pairs of input and output values ("stops"). Stop inputs must be numeric literals in strictly ascending
   * order. The output type must be number, array<number>, or color. enum "linear":interpolates linearly between the
   * pair of stops just less than and just greater than the input. enum "interval": return the output value of the stop
   * just less than the input.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, const char*)
   * @parameters GradientType_
   * @default "linear"
   */
  LayerPropertyFlag_LineGradientType,

  /**
   * @brief Display the Part between the start and {DisplayPart} of the line.
   *        The property requires 'LineMetrics' is true.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float,  const char*)
   * @parameters displayPart, range:[-1,1]
   * @default 1.0f
   */
  LayerPropertyFlag_LineDisplayPart,

  /**
   * @brief Sorts features in ascending order based on this value. Features with a higher sort key will appear above
   * features with a lower sort key.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, const char*,  const char*)
   * @default ""
   */
  LayerPropertyFlag_LineSortKey,
  
  /**
   * @brief The uv of color with which the line will be drawn.
   * @data-driven
   * @layout yes when it's data-driven express("{***}"), or not.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @parameters {r}, range:[0,1]
   * @default "0.0f"
   */
  LayerPropertyFlag_LineUV,

  /**
   * @brief Optional enum. One of "point", "line", "fill". Label placement relative to its geometry.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, const char*)
   * @parameters SymbolPlacementType_
   * @default "point"
   */
  LayerPropertyFlag_MarkerPlacement = 4000,

  /**
   * @brief Optional number greater than or equal to 1. Units in pixels. Defaults to 250. Requires symbol-placement to
   * be "line"
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @default 250
   */
  LayerPropertyFlag_MarkerSpacing,

  /**
   * @brief Optional boolean. If true, the symbols will not cross screen edges.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, bool, const char*)
   * @default true
   */
  LayerPropertyFlag_MarkerAvoidScreen,

  /**
   * @brief Optional boolean. If true, the symbols will not collision with each other.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, bool, const char*)
   * @default true
   */
  LayerPropertyFlag_MarkerCustomCollision,

  /**
   * @brief Display the Part between the start and {DisplayPart}
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float,  const char*)
   * @parameters displayPart, range:[-1,1]
   * @default 1.0f
   */
  LayerPropertyFlag_MarkerDisplayPart,

  /**
   * @brief Sorts features in ascending order based on this value. Features with a higher sort key will appear above
   * features with a lower sort key.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, const char*,  const char*)
   * @default ""
   */
  LayerPropertyFlag_MarkSortKey,

  /**
   * @brief The height of the entire symbol layer.
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @default 0.0
   */
  LayerPropertyFlag_MarkerHeight,


  /**
   * @brief Optional enum. One of "map", "viewport", "auto". Defaults to "auto". Orientation of text when map is
   * pitched.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, const char*)
   * @parameters AlignmentType_
   * @default "auto"
   */
  LayerPropertyFlag_TextPitchAlignment,

  /**
   * @brief Optional enum. One of "map", "viewport", "auto". Defaults to "auto". Orientation of text when map is
   * rotated.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, const char*)
   * @parameters AlignmentType_
   * @default "auto"
   */
  LayerPropertyFlag_TextRotationAlignment,

  /**
   * @brief Value to use for a text label. If a plain string is provided, it will be treated as a formatted with
   * default/inherited formatting options.
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, const char*,  const char*)
   * @default ""
   */
  LayerPropertyFlag_TextField,

  /**
   * @brief Font stack to use for displaying text.
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, const char*,  const char*)
   * @default "Source Han Sans CN Normal"
   */
  LayerPropertyFlag_TextFont,

  /**
   * @brief Font size. Optional number greater than or equal to 0. Units in pixels.
   * @data-driven y
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float,  const char*)
   * @default 16
   */
  LayerPropertyFlag_TextSize,

  /**
   * @brief The maximum line width for text wrapping. Optional number greater than or equal to 0.  Units in ems.
   * @data-driven y
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float,  const char*)
   * @default 8
   */
  LayerPropertyFlag_TextMaxWidth,

  /**
   * @brief Text leading value for multi-line text. Units in ems.
   * @data-driven y
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float,  const char*)
   * @default 1.2
   */
  LayerPropertyFlag_TextLineHeight,

  /**
   * @brief Text tracking amount. Units in ems.
   * @data-driven y
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float,  const char*)
   * @default 0
   */
  LayerPropertyFlag_TextLetterSpacing,

  /**
   * @brief Optional enum. One of  "left", "center", "right". Requires text-field.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, const char*)
   * @parameters TextJustifyType_
   * @default "center"
   */
  LayerPropertyFlag_TextJustify,

  /**
   * @brief Optional enum. One of "center", "left", "right", "top", "bottom", "top-left", "top-right", "bottom-left",
   * "bottom-right". Requires text-field.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, const char*)
   * @parameters SymbolAnchorType_
   * @default "center"
   */
  LayerPropertyFlag_TextAnchor,

  /**
   * @brief Distance that the text's anchor is moved from its original placement. Positive values indicate right and
   * down, while negative values indicate left and up.
   * @data-driven y
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @parameters {AnchorX, AnchorY}
   * @default {0.5, 0.5}
   */
  LayerPropertyFlag_TextAnchorXY,

  /**
   * @brief Maximum angle change between adjacent characters.
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float,  const char*)
   * @default 0
   */
  LayerPropertyFlag_TextMaxAngle,

  /**
   * @brief Rotates the text clockwise.
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float,  const char*)
   * @default 0
   */
  LayerPropertyFlag_TextRotate,

  /**
   * @brief Size of the additional area around the text bounding box used for detecting symbol collisions. Units in
   * pixels.
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float,  const char*)
   * @default 2
   */
  LayerPropertyFlag_TextPadding,

  /**
   * @brief Offset distance of text from its anchor. Positive values indicate right and down, while negative values
   * indicate left and up. If used with text-variable-anchor, input values will be taken as absolute values. Offsets
   * along the x- and y-axis will be applied automatically based on the anchor position.
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @parameters {offsetX,offsetY}
   * @default {0, 0}
   */
  LayerPropertyFlag_TextOffset,

  /**
   * @brief If true, the text will be visible even if it collides with other previously drawn symbols.
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, bool, const char*)
   * @default false
   */
  LayerPropertyFlag_TextAllowOverlap,

  /**
   * @brief If true, other symbols can be visible even if they collide with the text.
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, bool, const char*)
   * @default false
   */
  LayerPropertyFlag_TextIgnorePlacement,

  /**
   * @brief If true, icons will display without their corresponding text when the text collides with other symbols and
   * the icon does not.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, bool, const char*)
   * @default false
   */
  LayerPropertyFlag_TextOptional,

  /**
   * @brief The opacity at which the text will be drawn.
   * @data-driven y
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @parameters opatity, range:[0,1]
   * @default 1.0
   */
  LayerPropertyFlag_TextOpacity,

  /**
   * @brief The color with which the text will be drawn.
   * @data-driven y
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @parameters {r,g,b,a}, range:[0,1]
   * @default "#000000"
   */
  LayerPropertyFlag_TextColor,

  /**
   * @brief The color of the text's halo, which helps it stand out from backgrounds.
   * @data-driven y
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @parameters {r,g,b,a}, range:[0,1]
   * @default "#00000000"
   */
  LayerPropertyFlag_TextHaloColor,

  /**
   * @brief Distance of halo to the font outline. Max text halo width is 1/4 of the font-size.
   * @data-driven y
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @default 0
   */
  LayerPropertyFlag_TextHaloWidth,

  /**
   * @brief The halo's fadeout distance towards the outside. Units in pixels.
   * @data-driven y
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @default 0
   */
  LayerPropertyFlag_TextHaloBlur,

  /**
   * @brief Name of image in backgounrd of text.
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, const char*,  const char*)
   * @default ''"
   */
  LayerPropertyFlag_TextBgName,

  /**
   * @brief The size of image in backgounrd of text.
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @parameters opatity, range:[0,1]
   * @default 1.0
   */
  LayerPropertyFlag_TextBgSize,

  /**
   * @brief Distance that the text's center to background top/right/down/left
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @parameters {top,right,bottom,left}
   * @default {2,2,2,2}
   */
  LayerPropertyFlag_TextBgPadding,

  /**
   * @brief The color with which the text background will be drawn.
   * @data-driven y
   * @layout y.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @parameters {r,g,b,a}, range:[0,1]
   * @default "#FF0000"
   */
  LayerPropertyFlag_TextBgColor,

  /**
   * @brief The color with which the text whole region will be drawn.
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @parameters {r,g,b,a}, range:[0,1]
   * @default "#000000"
   */
  LayerPropertyFlag_TextRegionFillColor,

  /**
   * @brief Optional boolean. If true, the text will draw once at most
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, bool, const char*)
   * @default true
   */
  LayerPropertyFlag_TextUnique,

  //
  /**
   * @brief Symbol单位制：米、象素
   * @data-driven n
   * @layout y
   * @default "UnitType::Pixel"
   */
  LayerPropertyFlag_TextUnit,
  
  /**
   * @brief Symbol环绕优先级
   * @data-driven y
   * @layout y
   * @default 4660，默认效果(下->左->右->上)，换算公式如下:
   *  (top_pri = 1、right_pri = 2、int left_pri = 3、bottom_pri = 4，(top_pri << 12 | right_pri << 8 |  left_pri << 4 | bottom_pri) => 4660
   *  注: 下对应top_pri， 因为锚点anchorType = top时，效果是在图标下方。
   */
  LayerPropertyFlag_TextAroundPriority,

  /**
   * @brief Optional boolean. If true, the icon will be visible even if it collides with other previously drawn symbols.
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, bool, const char*)
   * @default false
   */
  LayerPropertyFlag_IconAllowOverlap,

  /**
   * @brief Optional boolean. If true, other symbols can be visible even if they collide with the icon.
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, bool, const char*)
   * @default false
   */
  LayerPropertyFlag_IconIgnorePlacement,

  /**
   * @brief Optional boolean. If true, text will display without their corresponding icons when the icon collides with
   * other symbols and the text does not.
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, bool, const char*)
   * @default false
   */
  LayerPropertyFlag_IconOptional,

  /**
   * @brief Optional enum. One of "map", "viewport", "auto". Defaults to "auto". Requires icon-image. In combination
   * with symbol-placement, determines the rotation behavior of icons.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, const char*)
   * @parameters AlignmentType_
   * @default "auto"
   */
  LayerPropertyFlag_IconRotationAlignment,

  /**
   * @brief Scales the original size of the icon by the provided factor. The new pixel size of the image will be the
   * original pixel size multiplied by icon-size. 1 is the original size; 3 triples the size of the image. Units in
   * factor of the original icon size.
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @default 1.0
   */
  LayerPropertyFlag_IconSize,

  /**
   * @brief Optional enum. One of "none", "width", "height", "both". Requires icon-image. Requires text-field. Scales
   * the icon to fit around the associated text.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, const char*)
   * @parameters IconTextFitType_
   * @default "none"
   */
  LayerPropertyFlag_IconTextFit,

  /**
   * @brief Size of the additional area added to dimensions determined by icon-text-fit, in clockwise order: top, right,
   * bottom, left.
   * @data-driven n
   * @layout y.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @parameters {top,right,bottom,left}
   * @default {0, 0, 0, 0}
   */
  LayerPropertyFlag_IconTextFitPadding,

  /**
   * @brief Name of image in backgounrd of icon
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, const char*,  const char*)
   * @default ''"
   */
  LayerPropertyFlag_IconImage,

  /**
   * @brief Rotates the icon clockwise.Units in degrees.
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @default 0
   */
  LayerPropertyFlag_IconRotate,

  /**
   * @brief Size of the additional area around the icon bounding box used for detecting symbol collisions. Units in
   * pixels.
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @default 2.0
   */
  LayerPropertyFlag_IconPadding,

  /**
   * @brief Offset distance of icon from its anchor. Positive values indicate right and down, while negative values
   * indicate left and up. Each component is multiplied by the value of icon-size to obtain the final offset in pixels.
   * When combined with icon-rotate the offset will be as if the rotated direction was up.
   * @data-driven y
   * @layout y.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @default {0, 0}
   */
  LayerPropertyFlag_IconOffset,

  /**
   * @brief Optional enum. One of "map", "viewport", "auto". Orientation of icon when map is pitched.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, const char*)
   * @parameters AlignmentType_
   * @default "auto"
   */
  LayerPropertyFlag_IconPitchAlignment,

  /**
   * @brief The opacity at which the icon will be drawn.
   * @data-driven y
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @parameters opatity, range:[0,1]
   * @default 1.0
   */
  LayerPropertyFlag_IconOpacity,

  /**
   * @brief The color of the icon. This can only be used with sdf icons.
   * @data-driven y
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @parameters {r,g,b,a}, range:[0,1]
   * @default "#000000"
   */
  LayerPropertyFlag_IconColor,

  /**
   * @brief The color with which the icon whole region will be drawn.
   * @data-driven y
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @parameters {r,g,b,a}, range:[0,1]
   * @default "#000000"
   */
  LayerPropertyFlag_IconWholeRegionFillColor,

  /**
   * @brief Optional enum. One of "center", "left", "right", "top", "bottom", "top-left", "top-right", "bottom-left",
   * "bottom-right". Part of the icon placed closest to the anchor.
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, const char*)
   * @parameters SymbolAnchorType_
   * @default "center"
   */
  LayerPropertyFlag_IconAnchor,

  /**
   * @brief Distance that the icon's anchor is moved from its original placement. Positive values indicate right and
   * down, while negative values indicate left and up.
   * @data-driven y
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @parameters {AnchorX, AnchorY}
   * @default {0.5, 0.5}
   */
  LayerPropertyFlag_IconAnchorXY,
  
  
  /**
   * @brief Optional enum. One of "none", "small", "aggregate".
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, const char*)
   * @default none
   */
  LayerPropertyFlag_MarkerCollisionType,
  
  /**
   * @brief collision mask,  [31-16] is type mask, base source use 0x8000, [15-0] is collision mask
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, double)
   * @default 0xffff0000
   */
  LayerPropertyFlag_MarkerCollisionMask,

  // Circle
  /**
   * @brief Circle radius.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float,  const char*)
   * @default 5.0f
   */
  LayerPropertyFlag_CircleRadius = 5000,

  /**
   * @brief The Unit of circle radius.
   * enum "map": Units in meters.
   * enum "viewport": Units in pixels.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, const char*)
   * @parameters AnchorType_
   * @default "viewport"
   */
  LayerPropertyFlag_CircleRadiusScale,

  /**
   * @brief The fill color of the circle.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int,  const char*)
   * @parameters {r,g,b,a}, range:[0,1]
   * @default "#000000"
   */
  LayerPropertyFlag_CircleColor,

  /**
   * @brief Amount to blur the circle. 1 blurs the circle such that only the centerpoint is full opacity.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @default 0.0f
   */
  LayerPropertyFlag_CircleBlur,

  /**
   * @brief The opacity at which the circle will be drawn.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @parameters opatity, range:[0,1]
   * @default 1.0f
   */
  LayerPropertyFlag_CircleOpacity,

  /**
   * @brief The geometry's offset. Values are [x, y] where negatives indicate left and up, respectively.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int,  const char*)
   * @parameters {TranslateX,TranslateY}
   * @default {}
   */
  LayerPropertyFlag_CircleTranslate,

  /**
   * @brief Controls the frame of reference for circle-translate.
   * enum "map": The circle is translated relative to the map.
   * enum "viewport": The circle is translated relative to the viewport.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, const char*)
   * @parameters AnchorType_
   * @default "map"
   */
  LayerPropertyFlag_CircleTranslateAnchor,

  /**
   * @brief Controls the scaling behavior of the circle when the map is pitched.
   * enum "map": Circles are scaled according to their apparent distance to the camera.
   * enum "viewport": Circles are not scaled.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, const char*)
   * @parameters AnchorType_
   * @default {}
   */
  LayerPropertyFlag_CirclePitchScale,

  /**
   * @brief Orientation of circle when map is pitched.
   * enum "map": The circle is aligned to the plane of the map.
   * enum "viewport": The circle is aligned to the plane of the viewport.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, const char*)
   * @parameters AnchorType_
   * @default "viewport"
   */
  LayerPropertyFlag_CirclePitchAlignment,

  /**
   * @brief The width of the circle's stroke. Strokes are placed outside of the circle-radius.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @default 0.0f
   */
  LayerPropertyFlag_CircleStrokeWidth,

  /**
   * @brief The stroke color of the circle.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int,  const char*)
   * @parameters {r,g,b,a}, range:[0,1]
   * @default "#000000"
   */
  LayerPropertyFlag_CircleStrokeColor,

  /**
   * @brief The opacity of the circle's stroke.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float,  const char*)
   * @parameters opacity, range:[0,1]
   * @default 1.0f
   */
  LayerPropertyFlag_CircleStrokeOpacity,

  /**
   * @brief The real part and imaginary part of the circle's stroke.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int,  const char*)
   * @default {0.0f, 0.0f}: the normal stroke
   */
  LayerPropertyFlag_CircleDashStroke,

  /**
   * @brief The start position and end position of arc.
   * @data-driven n
   * @layout n
   * @unit radian
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int,  const char*)
   * @default {0.0f, 0.0f}: circle not arc.
   */
  LayerPropertyFlag_CircleArc,

  /**
   * @brief Sorts features in ascending order based on this value. Features with a higher sort key will appear above
   * features with a lower sort key.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, const char*,  const char*)
   * @default ""
   */
  LayerPropertyFlag_CircleSortKey,

  /**
   * @brief reverse display circle.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, bool,  const char*)
   * @default false
   */
  LayerPropertyFlag_CircleReverse,

  /**
   * @brief set the color ramp to the stroke of the color.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*,  int)
   * @default false
   */

  LayerPropertyFlag_CircleColorRamp,

  // Heatmap
  /**
   * @brief Radius of influence of one heatmap point in pixels. Increasing the value makes the heatmap smoother, but
   * less detailed.
   * @data-driven y
   * @layout yes when it's data-driven express("{***}"), or not.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float,  const char*)
   * @default 30.0f
   */
  LayerPropertyFlag_HeatmapRadius = 6000,

  /**
   * @brief The Unit of heatmap radius.
   * enum "map": Units in meters.
   * enum "viewport": Units in pixels.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, const char*)
   * @parameters UnitType_
   * @default "pixel
   */
  LayerPropertyFlag_HeatmapRadiusUnit,

  /**
   * @brief A measure of how much an individual point contributes to the heatmap. A value of 10 would be equivalent to
   * having 10 points of weight 1 in the same spot. Especially useful when combined with clustering.
   * @data-driven y
   * @layout yes when it's data-driven express("{***}"), or not.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float,  const char*)
   * @default 1.0f
   */
  LayerPropertyFlag_HeatmapWeight,

  /**
   * @brief The min and max of intensity. Similar to heatmap-weight but controls the intensity of the heatmap globally.
   * Primarily used for adjusting the heatmap based on zoom level.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int, const char*)
   * @default {0.0f 1.0f}
   */
  LayerPropertyFlag_HeatmapIntensity,

  /**
   * @brief Defines the color of each pixel based on its density value in a heatmap.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int , const char*)
   * @parameters {key1,r1,g1,b1,a1,key2,r2,g2,b2,a2...}
   * @default {}
   */
  LayerPropertyFlag_HeatmapColor,

  /**
   * @brief The global opacity at which the heatmap layer will be drawn.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float,  const char*)
   * @parameters opacity, range:[0,1]
   * @default 1.0f
   */
  LayerPropertyFlag_HeatmapOpacity,

  /**
   * @brief heatmap shape.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, int, const char*)
   * @parameters HeatMapRenderType_
   * @default HeatMapType::Circle
   */
  LayerPropertyFlag_HeatmapType,

  /**
   * @brief heatmap size.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @parameters size, unite: meter
   * @default 2000.0f
   */
  LayerPropertyFlag_HeatmapSize,

  /**
   * @brief heatmap gap.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @parameters gap, unite: meter
   * @default 10.0f
   */
  LayerPropertyFlag_HeatmapGap,

  /**
   * @brief heatmap center latitude.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @parameters latitude (-90.0, 90.0)
   * @default 0.0f
   */
  LayerPropertyFlag_HeatmapCenterLatitude,

  // raster
  /**
   * @brief The opacity at which the image will be drawn.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float,  const char*)
   * @parameters opacity, range:[0,1]
   * @default 1.0f
   */
  LayerPropertyFlag_RasterOpacity = 7000,

  /**
   * @brief The color threshold above which the pixel will not be drawn.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float, const char*)
   * @default #FFFFFF
   */
  LayerPropertyFlag_RasterColorThreshold = 7001,

  /**
   * @brief Defines the color of each pixel based on its value in type channel.
   * @example: "".
   * @data-driven y
   * @layout y
   * @default {}
   */
  LayerPropertyFlag_RasterColor = 7002,

  /**
   * @brief Defines model path
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, const char*, const char*)
   * @default ""
   */
  LayerPropertyFlag_ModelPath = 8000,

  /**
   * @brief Defines model matrix
   * @data-driven y
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, char*,  const char*)
   * @default {0,0,0,0,0,0,1,1,1}
   */
  LayerPropertyFlag_ModelMatrix = 8001,
#if ENABLE_3D
  /**
   * @brief The color with which the line-volume will be drawn.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int,  const char*)
   * @parameters {r,g,b,a}, range:[0,1]
   * @default "#000000"
   */
  LayerPropertyFlag_LineVolumeColor = 9000,

  /**
   * @brief The corss shape with which the line-volume will be drawn.
   * @data-driven y
   * @layout yes when it's data-driven express("{***}"), or not.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, const char*,  const char*)
   * @default ""
   */
  LayerPropertyFlag_LineVolumeShape,

  /**
   * @brief The corss-shape's offset, a positive value offsets the cross-shape to the right and up , and a negative
   * value to the left and down.
   * @data-driven y
   * @layout y.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int,  const char*)
   * @parameters {TranslateX,TranslateY}
   * @default {0,0}
   */
  LayerPropertyFlag_LineVolumeOffset,

  /**
   * @brief The height at which the line-volume will be drawn. Units in meters.
   * @data-driven y
   * @layout yes when it's data-driven express("{***}"), or not.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float,  const char*)
   * @default 0.0f
   */
  LayerPropertyFlag_LineVolumeHeight,

  /**
   * @brief Sorts features in ascending order based on this value. Features with a higher sort key will appear above
   * features with a lower sort key.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, const char*,  const char*)
   * @default ""
   */
  LayerPropertyFlag_LineVolumeSortKey,

  /**
   * @brief The color with which the point-volume will be drawn.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int,  const char*)
   * @parameters {r,g,b,a}, range:[0,1]
   * @default "#000000"
   */
  LayerPropertyFlag_PointVolumeColor = 10000,

  /**
   * @brief The description of  volume to be drawn.
   * @data-driven y
   * @layout yes when it's data-driven express("{***}"), or not.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, const char*,  const char*)
   * @default ""
   */
  LayerPropertyFlag_PointVolumeShape,

  /**
   * @brief The pointVolume's offset at x, y or z axis.
   * @data-driven y
   * @layout y.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float*, int,  const char*)
   * @parameters {TranslateX,TranslateY,TranslateZ}
   * @default {0,0,0}
   */
  LayerPropertyFlag_PointVolumeOffset,

  /**
   * @brief The height at which the point-volume will be drawn. Units in meters..
   * @data-driven y
   * @layout yes when it's data-driven express("{***}"), or not.
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float,  const char*)
   * @default 0.0f
   */
  LayerPropertyFlag_PointVolumeHeight,

  /**
   * @brief The rotation of volume.
   * @data-driven n
   * @layout n
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, float,  const char*)
   * @parameters radian, range:[-M_PI, M_PI]
   * @default 0.0f
   */
  LayerPropertyFlag_PointVolumeRotation,

  /**
   * @brief Sorts features in ascending order based on this value. Features with a higher sort key will appear above
   * features with a lower sort key.
   * @data-driven n
   * @layout y
   * @function setLayerProperty(LayerHandle, LayerPropertyFlag, const char*,  const char*)
   * @default ""
   */
  LayerPropertyFlag_PointVolumeSortKey
#endif
};

// flag for setFeature and getFeatureType
enum FeatureTypeFlag_ : int32_t {
  // data:{lat, lon1}
  // dataLen:1
  // startInd:NULL
  FeatureTypeFlag_Point,

  // data:{lon_0,lat_0,lon_1,lat_1,lon_2,lat_2,lon_3,lat_3,...,lon_n-1, lat_n-1}
  // dataLen:n
  // startInd:NULL
  FeatureTypeFlag_MultiPoint,

  // data:{lon_0,lat_0,lon_1,lat_1,lon_2,lat_2,lon_3,lat_3,...,lon_n-1, lat_n-1}
  // dataLen:n
  // startInd:NULL
  FeatureTypeFlag_Line,

  // data:{lon_0,lat_0,lon_1,lat_1,lon_2,lat_2,...
  //       lon_a,lat_a,lon_a+1, lat_a+1, lon_a+2, lat_a+2,...,
  //       ...
  //       lon_b,lat_b,lon_b+1, lat_b+1, lon_b+2, lat_b+2}
  // dataLen: the total num of points(the element num of data divided by 2)
  // startInd:{0, 2a, ..., 2b}
  // startEndLen: the element num of startInd
  // the multilines: {0,1,2...},{a,a+1,a+2...},...,{b,b+1,b+2}
  FeatureTypeFlag_MultiLine,

  // case1: simple polygon
  // data:{lon_0,lat_0,lon_1,lat_1,lon_2,lat_2,...}
  // dataLen: the total num of points(the element num of data divided by 2)
  // startInd: NULL
  // startEndLen: 0
  // the polygon: {0,1,2...}
  // -------------------------------------------------------
  // case2: complex polygon
  // data:{lon_0,lat_0,lon_1,lat_1,lon_2,lat_2,...
  //       lon_a,lat_a,lon_a+1, lat_a+1, lon_a+2, lat_a+2,...,
  //       ...
  //       lon_b,lat_b,lon_b+1, lat_b+1, lon_b+2, lat_b+2}
  // dataLen: the total num of points(the element num of data divided by 2)
  // startInd:{0, 2a, ..., 2b}
  // startEndLen: the element num of startInd
  // the multilines: {0,1,2...},{a,a+1,a+2...},...,{b,b+1,b+2}
  FeatureTypeFlag_Polygon,

  // not supported when setFeature, but the result of query(getFeatureType()) can be multipolygon
  FeatureTypeFlag_MultiPolygon,

  FeatureTypeFlag_Unknown
};

// for getFeaturePropertyType()
enum FeaturePropertyType_ : int32_t {
  FeaturePropertyType_None = 0,
  FeaturePropertyType_Bool,
  FeaturePropertyType_Long,
  FeaturePropertyType_Double,
  FeaturePropertyType_String
};

// for online request host
enum HostType_ : int32_t { HostType_Prod = 0, HostType_Stage, HostType_Prod_HK_Macao };

enum EventSeverityType_ : int32_t {
  EventSeverityType_Debug,
  EventSeverityType_Info,
  EventSeverityType_Warning,
  EventSeverityType_Error,
};

enum EventType_ : int32_t {
  EventType_General,
  EventType_ParseStyle,
  EventType_ParseTile,
  EventType_Render,
  EventType_Style,
  EventType_Database,
  EventType_HttpRequest,
  EventType_Image,
  EventType_OpenGL,
  EventType_JNI,
  EventType_Android,
  EventType_Crash,
  EventType_Glyph,
  EventType_Performance,
  EventType_Tile
};

enum EventCodeFlag_ : int64_t {
  EventCodeFlag_CodeGeneralThread = 100001,
  EventCodeFlag_CodeGeneralInitFileSource = 100002,
  EventCodeFlag_CodeGeneralClock = 100003,
  EventCodeFlag_CodeGeneralUncaughtException = 100100,

  EventCodeFlag_CodeParseStyleCommon = 200001,

  EventCodeFlag_CodeRenderExtrusionPattern = 400001,
  EventCodeFlag_CodeRenderUncaughtException = 400100,

  EventCodeFlag_CodeStyleSource = 500001,
  EventCodeFlag_CodeStyleResponse = 500002,
  EventCodeFlag_CodeStyleParse = 500003,
  EventCodeFlag_CodeStyleInternalStyle = 500004,
  EventCodeFlag_CodeStyleNotFind = 500005,
  EventCodeFlag_CodeStyleLoaded = 500006,

  EventCodeFlag_CodeDatabaseGetResource = 600001,
  EventCodeFlag_CodeDatabaseClose = 600002,
  EventCodeFlag_CodeDatabaseOpen = 600003,
  EventCodeFlag_CodeDatabaseRemove = 600004,
  EventCodeFlag_CodeDatabaseGlyph = 600005,
  EventCodeFlag_CodeDatabaseCallback = 600006,
  EventCodeFlag_CodeDatabaseClearData = 600007,

  EventCodeFlag_CodeHttpRequestCommon = 700001,
  EventCodeFlag_CodeHttpRequestStyle = 700002,
  EventCodeFlag_CodeHttpRequestSource = 700003,
  EventCodeFlag_CodeHttpRequestTile = 700004,

  EventCodeFlag_CodeImageNotFind = 800001,
  EventCodeFlag_CodeImageCreate = 800002,

  EventCodeFlag_CodeOpenGLSprite = 900001,
  EventCodeFlag_CodeOpenGLLineAtlas = 900002,

  EventCodeFlag_CodeJNIGeoJSON = 1000001,
  EventCodeFlag_CodeJNIRunloop = 1000003,

  EventCodeFlag_CodeAndroidBitmap = 1100001,
  EventCodeFlag_CodeAndroidRunloop = 1100002,

  EventCodeFlag_CodeCrashThread = 1200001,

  EventCodeFlag_CodeGlyphDuplicate = 1300001,
  EventCodeFlag_CodeGlyphEmpty = 1300002,
  EventCodeFlag_CodeGlyphErrorThread = 1300003,
  EventCodeFlag_CodeGlyphDefaultFontInfo = 1300004,

  EventCodeFlag_CodeTileCommon = 1400001,
  EventCodeFlag_CodeTileFinishLoad = 1400002,
  EventCodeFlag_CodeTileBuild = 1400003,
  EventCodeFlag_CodeTileBuildError = 1400004,
  EventCodeFlag_CodeTileBuildTryUBOFailed = 1400005,

  EventCodeFlag_CodeRenderFinish = 1500001,
  EventCodeFlag_CodeRenderMapScreenBlank = 1500002,

  EventCodeFlag_CodeDynamicLoadStyle = 1600001
};

// http error type in android
enum HttpErrorType_ : int32_t {
  HttpErrorType_Connection = 0,
  HttpErrorType_Temporary = 1,
  HttpErrorType_Permanent = 2,
  HttpErrorType_NotConnectedToInternet = 3
};

// URL error codes in ios
enum URLErrorCode_ : int32_t {
  // An asynchronous load has been canceled.
  URLError_Cancelled = -999,
  // An asynchronous operation timed out.
  URLError_TimedOut = -1001,
  // The host name for a URL couldn’t be resolved.
  URLError_CannotFindHost = -1003,
  // An attempt to connect to a host failed.
  URLError_CannotConnectToHost = -1004,
  // A client or server connection was severed in the middle of an in-progress load.
  URLError_NetworkConnectionLost = -1005,
  // The host address couldn’t be found via DNS lookup.
  URLError_DNSLookupFailed = -1006,
  // A network resource was requested, but an internet connection has not been established and can’t be established automatically.
  URLError_NotConnectedToInternet = -1009,
  // The attempted connection required activating a data context while roaming, but international roaming is disabled.
  // ios 3.0 API_AVAILABLE
  URLError_InternationalRoamingOff = -1018,
  // A connection was attempted while a phone call was active on a network that doesn’t support simultaneous phone and data communication, such as EDGE or GPRS.
  // ios 3.0 API_AVAILABLE
  URLError_CallIsActive = -1019,
  // The cellular network disallowed a connection.
  // ios 3.0 API_AVAILABLE
  URLError_DataNotAllowed = -1020
};

// HTTP response status Code
enum ResponseStatusCode_ : int32_t {
  // Standard response for successful HTTP requests.
  ResponseStatusCode_New = 200,
  // The server successfully processed the request, and is not returning any content.
  ResponseStatusCode_NoContent = 204,
  // The server successfully processed the request, but is not returning any content. Unlike a 204 response, this response requires that the requester reset the document view.
  ResponseStatusCode_ResetContent = 205,
  // Indicates that the resource has not been modified since the version specified by the request headers If-Modified-Since or If-None-Match. In such case, there is no need to retransmit the resource since the client still has a previously-downloaded copy.
  ResponseStatusCode_NoChange = 304,
  // The requested resource could not be found
  ResponseStatusCode_NotFound = 404,
  // The user has sent too many requests in a given amount of time. Intended for use with rate-limiting schemes.
  ResponseStatusCode_TooManyRequests = 429,
  // Response status codes beginning with the digit "5" indicate cases in which the server is aware that it has encountered an error or is otherwise incapable of performing the request.
  // Valid code is [500,600)
  ResponseStatusCode_ServerError = 500,
  // Other unknown reasons
  ResponseStatusCode_Other = 600,
};

// Performance Log Type
enum PerformanceLogType_ : int32_t{
  // FPS log output with system platform log
  FPS = 1,
  // TileLife log output path:
  //   Android  /storage/emulated/0/Android/data/[PackageName]/cache/sankuai.tileInfo
  //   iOS ./Library/Caches/sankuai.tileInfo
  TileLife = 2,
};

typedef int32_t ErrorType;
typedef int32_t FileSourceTypeFlag;
typedef int32_t MapModeFlag;
typedef int32_t CameraOptionsFlag;
typedef int32_t CameraOptionsRangeFlag;
typedef int32_t LayerOrderType;
typedef int32_t OverlayLayerOrderType;
typedef int32_t LayerPropertyFlag;
typedef int32_t FeatureTypeFlag;
typedef int32_t SourceTypeFlag;
typedef int32_t ThreadModeFlag;
typedef int32_t TrafficLevel;
typedef int32_t FeaturePropertyType;
typedef int32_t TileCacheType;
typedef int32_t CaptureRenderMask;
typedef int32_t HostType;
typedef int32_t LocalResType;
typedef int32_t EventSeverityType;
typedef int32_t EventType;
typedef int32_t WeatherType;
typedef uint8_t RenderBackendType;
typedef int32_t BasemapSourceTypeFlag;
typedef int32_t StyleLoadingFlag;
typedef int32_t HttpErrorType;
typedef int32_t URLErrorCode;
typedef int32_t ResponseStatusCode;
typedef int32_t PerformanceLogType;
typedef int32_t AntiAliasingTypeFlag;

typedef int64_t GeojsonSourceHandle;
typedef int64_t ImageSourceHandle;
typedef int64_t RasterSourceHandle;
typedef int64_t LayerHandle;
typedef int64_t FeaturesHandle;
typedef int64_t ArrowHandle;
typedef int64_t EventCodeFlag;

namespace net {
class RequestTask {
 public:
  virtual void cancel() = 0;
  virtual ~RequestTask() = default;
};

#if TARGET_OS_IOS || TARGET_OS_OSX
// req: NSMutableURLRequest*
// data: NSData*
// res: NSURLResponse*
// error: NSError*
  typedef std::shared_ptr<RequestTask> (*OnSendHttpRequestHandle)(
      void* req, void* customData, std::function<void(void* data, void* res, void* error)> handle);

  extern void setHttpHooker(OnSendHttpRequestHandle reqHandle);

#elif __ANDROID__
  struct URLRequest {
    const char* url;
    const char* etag;
    const char* modified;
    const char* body;
    const char* userURLParameters;
  };

  struct URLResponse {
    int code = 200;
    const char* etag;
    const char* modified;
    const char* cacheControl;
    const char* expires;
    const char* retryAfter;
    const char* xRateLimitReset;
    const char* body;
    uint64_t bodyLen;
  };

  struct URLError {
    HttpErrorType errorType;
    const char* message;
  };

  typedef std::shared_ptr<RequestTask> (*OnSendHttpRequestHandle)(void* req, int* customUserDatas, int32_t len,
                                                                  std::function<void(void* res, void* error)> callback);
  extern RENDER_API void setHttpHooker(OnSendHttpRequestHandle reqHandle);
#endif
}  // namespace net

typedef bool (*onRecordHandle)(EventSeverityType severity, EventType event, int64_t code, const std::string& msg);
typedef void (*onAlarmRecordHandle)(EventSeverityType severity, EventType event, int64_t code,
                                    const std::string& codeStr, const std::string& msg);

extern RENDER_API void setLogObserver(onRecordHandle onRecord, onAlarmRecordHandle onAlarmRecord);

// get center and zoom that transforms the camera such that the specified latitude/longitude bounds are centered on
// screen at the greatest possible zoom level while maintaining current camera position bearing and EdgeInsets values.
// width:  Screen width(pixel)
// height: Screen height(pixel)
// bounds: (sw latitude, sw longitude, ne latitude, ne longitude)
// edgeInset: numbers of pixels from the top/left/botton/right edge
// return ErrorType_InvalidPara if lat is out of range[-90,90] or lon infinite
extern RENDER_API ErrorType CameraForLatLngBounds(float width, float height, double (&bounds)[4], double (&edgeInsets)[4], double& lat, double& lon, double& zoom, double bearing = 0.0);


// get center and zoom that transforms the camera such that the specified latitude/longitude lists are centered on
// screen at the greatest possible zoom level
// width:  MapSize宽度，屏幕空间dp像素单位(不乘pixelRatio)
// height: MapSize高度，屏幕空间dp像素单位(不乘pixelRatio)
// latLonList : polygon经纬度数组，顺序为lat1/lng1/lat2/lng2...，此值为nullptr，表示无效，不执行后续逻辑, 首尾相连表示面，否则表示线
// latLonLen : latLonList长度，此值为0，表示无效，不执行计算逻辑
// marginList : polygon每个顶点外扩像素，屏幕空间dp像素单位(不乘pixelRatio)，MapSize左上角为原点；marginList可以为空，此值不为空时，要求与latLonList点顺序完全一致
// scrnCoordList: 控制显示的屏幕范围，屏幕空间dp像素单位(不乘pixelRatio),顺序为x1/y1/x2/y2..., 首尾相连表示面，否则表示线
// coordLen : scrnCoordList长度，此值为0，表示无效，不执行计算逻辑
// lat : 返回值，地图中心点纬度
// lon : 返回值，地图中心点经度
// zoom : 返回值，比例尺
// polygonBuffer : polygon外扩像素，屏幕空间dp像素单位(不乘pixelRatio)
// detalZoom : zoom缩小限制，默认最大缩小2级
// return ErrorType_InvalidPara if latLonLen is zero or coordLen is zero or scrnCoords is nullptr or latLonList is nullptr or (marginLen != 0 && (marginLen * 2) != latLonLen)
extern RENDER_API ErrorType CameraForLatLngList(float width, float height, double* latLonList, int32_t latLonLen, double* marginList,  double* scrnCoordList, int32_t coordLen, double& lat, double& lon, double& zoom, double polygonBuffer = 0, double detalZoom = 2);

class Map;

/*
 说明：
 1. 当view不为空时，renderType将失效，根据view类型确定图形驱动类型(OpenGL/Metal)
 2. 当view为空时：
    - render为true时，根据renderType类型确定图形驱动类型(OpenGL/Metal)
    - render为false时，renderType将失效，不进行绘制
 */
struct IMapOptions {
  MapModeFlag mapMode = MapModeFlag_Continuous;
  int threadNum = 4;

  FileSourceTypeFlag flag = FileSourceTypeFlag_DefaultFileSource;
  const char* msgExtra = "./testdb";
  
  // view : GLKView or MTKView or nullptr. if is nullptr,backend uses OpenGL env.
  void* view = nullptr;

  void* userData = nullptr;

  // userURLParameters : 网络请求参数列表，格式 key1=value1&key2=value2&...
  const char* userURLParameters = "";

  bool render = true;

  bool build = true;
  
  // 是否需要中断当前帧的render执行
  bool needBreakDraw = false;
  
  // 是否分离IMap与Map析构
  bool enableSeparateMapFree = false;

  // 引擎渲染功能开关，按位控制 第0位 NewSymbol 第1位 NewSymbolTile(底图)
  int renderFuncSwitch = 0;
  
  // graphics driver type, default is gl
  RenderBackendType renderType = RenderBackendType_OpenGL;
  // 底图类型，默认为矢量底图
  BasemapSourceTypeFlag basemapSourceType = BasemapSourceTypeFlag_Vector;
  // 抗锯齿类型，默认无抗锯齿
  AntiAliasingTypeFlag antiAliasType = AntiAliasingTypeFlag_None;
  
  // 本地样式压缩文件的二进制流数据
  const char* localStyleResBuffer = "";
  // 本地样式压缩文件的二进制流数据的大小
  int localStyleResBufferSize = 0;
  // 本地样式名称
  const char* localStyleName = "";
};

struct IRenderOptions {
  // waitScheduled:  valid only for Metal env.
  // If you wait for scheduling in metal env, please set waitScheduled true. only useful for mark synchronization.This
  // operation affects performance. WaitScheduled is generally true.
  bool waitScheduled = false;
  
  bool lightWeightRender = false;
  
  // calayer: valid only for Metal env.
  // calayer: CAMetalLayer object.
  void* calayer = nullptr;
  
  IRenderOptions(bool wait = false) :waitScheduled(wait),lightWeightRender(false),calayer(nullptr){}
};

struct ICaptureOptions {
  // waitScheduled:  valid only for Metal env.
  // If you wait for scheduling in metal env, please set waitScheduled true. only useful for mark synchronization.This
  // operation affects performance. WaitScheduled is generally true.
  bool waitScheduled = false;
  
  // calayer: valid only for Metal env.
  // calayer: CAMetalLayer object.
  void* calayer = nullptr;
};

struct IMapPrivate;
class IMap {
 public:
  IMap(Map* map);

  RENDER_API IMap(float width, float height, float pixelRatio, IMapOptions options);

  // view : valid only for Metal env.
  RENDER_API IMap(FileSourceTypeFlag type, const char* msgExtra, int32_t threadPoolNum, float width, float height,
       float pixelRatio, MapModeFlag mapMode = MapModeFlag_Continuous, void* view = nullptr, void* userData = nullptr,
       const char* userURLParameters = "");

  RENDER_API ~IMap();

  Map* getInternalMap() const;

  float getPixelRatio() const;

  RENDER_API ErrorType setMapSize(float width, float height);

  RENDER_API ErrorType getMapSize(float& width, float& height) const;

  // set camera parameters
  // cameraOption[0]~cameraOption[1]: center latitude, center longitude, nan for keeping unchanged
  // cameraOption[2]~cameraOption[5]: numbers of pixels from the top/left/botton/right edge, nan for keeping unchanged
  // cameraOption[6]~cameraOption[7]: anchorX, anchorY, nan for keeping unchanged
  // cameraOption[8]: zoom, nan for keeping unchanged
  // cameraOption[9]: bearing angle, nan for keeping unchanged
  // cameraOption[10]: pitch angle, nan for keeping unchanged
  // duration: time(ms) to animate to the viewpoint defined herein
  // frameCallback:It is called on each frame of the transition, just before a screen update, except on the last frame.
  // The first parameter indicates the elapsed time as a percentage of the duration.
  // finishCallback:It is called once on the last frame of the transition, just before the corresponding screen update.
  // bezierCoord: first and last control points: {p1x,p1y,p2x,p2y}
  // bezierCoordLen: the element num of bezierCoord
  // return ErrorType_InvalidPara if lat is out of range[-90,90] or lon infinite
  RENDER_API ErrorType setCameraOptions(double (&cameraOption)[11], int32_t duration = 0,
                             void (*frameCallback)(void*, double) = nullptr, void (*finishCallback)(void*) = nullptr,
                             void* userData = nullptr, double* bezierCoord = nullptr, int32_t bezierCoordLen = 0);

  // Set up a set of animations and execute them in sequence.
  // cameraOptLength: the element num of cameraOptions, it's a multiple of 16
  // cameraOption[n*16+0]~cameraOption[n*16+1]: center latitude, center longitude, nan for keeping unchanged
  // cameraOption[n*16+2]~cameraOption[n*16+5]: numbers of pixels from the top/left/botton/right edge, nan for keeping
  // unchanged cameraOption[n*16+6]~cameraOption[n*16+7]: anchorX, anchorY, nan for keeping unchanged
  // cameraOption[n*16+8]: zoom, nan for keeping unchanged
  // cameraOption[n*16+9]: bearing angle, nan for keeping unchanged
  // cameraOption[n*16+10]: pitch angle, nan for keeping unchanged
  // cameraOption[n*16+11]: time(ms) to animate to the viewpoint defined herein
  // cameraOption[n*16+12]: first control point's X of the bezier interpolation
  // cameraOption[n*16+13]: first control point's Y of the bezier interpolation
  // cameraOption[n*16+14]: last control point's X of the bezier interpolation
  // cameraOption[n*16+15]: last control point's Y of the bezier interpolation
  // frameCallback :It is called on each frame of the transition, just before a screen update, except on the last frame.
  // The second param is a parameter between 0 and 1. The third param is current animation index. finishCallback:It is
  // called once on the last frame of the transition, just before the corresponding screen update. The second param is
  // current animation index. The third parameter indicates whether the animation ends normally(true) or is
  // cancelled(false).
  RENDER_API ErrorType setCameraOptionGroup(double* cameraOptions, int32_t cameraOptLength,
                                 void (*frameCallback)(void*, double, int) = nullptr,
                                 void (*finishCallback)(void*, int, bool) = nullptr, void* userData = nullptr);

  RENDER_API ErrorType getCenter(double& lat, double& lon);

  RENDER_API ErrorType getZoom(double& zoom);

  RENDER_API ErrorType getBearing(double& bearing);

  RENDER_API ErrorType getPitch(double& pitch);
  
  // get camera params for origin and target camera options
  // cameraOption[0]~cameraOption[1]: target center latitude, target center longitude, nan for keeping unchanged
  // cameraOption[2]~cameraOption[5]: numbers of pixels from the top/left/botton/right edge, nan for keeping unchanged
  // cameraOption[6]~cameraOption[7]: anchorX, anchorY, nan for keeping unchanged
  // cameraOption[8]: zoom, nan for keeping unchanged
  // cameraOption[9]: bearing angle, nan for keeping unchanged
  // cameraOption[10]: pitch angle, nan for keeping unchanged
  // originOption[0]~originOption[1]: souoriginrce center latitude, origin center longitude, nan for current map's center
  // originOption[2]: origin zoom, nan for current map's zoom
  // originOption[3]: origin bearing angle, nan for current map's bearing angle
  // originOption[4]: origin pitch angle, nana for current map's pitch angle
  RENDER_API ErrorType getCameraParameterByOptions(double (&cameraOption)[11], double (&originOption)[5], double& latCenter, double& lonCenter, double& zoom, double& bearing, double& pitch);

  // set the max/min of camera paramters
  // return ErrorType_InvalidPara if lat is out of range[-90,90] or lon infinite or arr is null or arrLen is less than
  // needed. Special: for CameraOptionsRangeFlag_CenterBounds, set arr nullptr to remove the restriction
  RENDER_API ErrorType setCameraOptionsRange(double* arr, int32_t arrLen, CameraOptionsRangeFlag flag);

  // set camera eye's or center's params(If has 'centerLat'). NOTE: Parameter names cannot be modified!!
  // lat: camera eye's latitude
  // lng : camera eye's longitude
  // alt : camera eye's altitude
  // bearing:bearing angle, nan for keeping unchanged
  // zoom:zoom, nan for keeping unchanged
  // minfar:camera far, in meter, default is zero.
  // fov:field of view, in degree.
  // centerLat: camera center's latitude
  // centerLng: camera center's longitude
  // pitch : pitch angle, nan for keeping unchanged. Only used for center's params.
  RENDER_API ErrorType setCameraEyeParams(const char* eyeParams);

  RENDER_API ErrorType getCameraEye(double& lat, double& lon, double& alt);

  RENDER_API ErrorType setCameraInWebMercator(double eye[3], double center[3], double up[3]);

  // cancel the animation
  RENDER_API ErrorType cancelAnimation();
  
  [[deprecated]]
  const std::vector<std::string> getColorStyles();
  
  RENDER_API ErrorType getColorStyles(char (&version)[1024]);

  // move by unit of pixel
  // offsetX, offsetY: the offset of screen coordinate
  // duration: time(ms) to animate
  // frameCallback:It is called on each frame of the transition, just before a screen update, except on the last frame.
  // The first parameter indicates the elapsed time as a percentage of the duration. finishCallback:It is called once on
  // the last frame of the transition, just before the corresponding screen update.
  RENDER_API ErrorType moveBy(double offsetX, double offsetY, int32_t duration = 0, void (*frameCallback)(void*, double) = nullptr,
                   void (*finishCallback)(void*) = nullptr, void* userData = nullptr);

  // cameraOption[0]~cameraOption[1]: center latitude, center longitude, nan for keeping unchanged
  // cameraOption[2]~cameraOption[5]: numbers of pixels from the top/left/botton/right edge, nan for keeping unchanged
  // cameraOption[6]~cameraOption[7]: anchorX, anchorY, nan for keeping unchanged
  // cameraOption[8]: zoom, nan for keeping unchanged
  // cameraOption[9]: bearing angle, nan for keeping unchanged
  // cameraOption[10]: pitch angle, nan for keeping unchanged
  // duration: time(ms) to animate to the viewpoint defined herein
  // frameCallback:It is called on each frame of the transition, just before a screen update, except on the last frame.
  // The first parameter indicates the elapsed time as a percentage of the duration.
  // finishCallback:It is called once on the last frame of the transition, just before the corresponding screen update.
  // return ErrorType_InvalidPara if lat is out of range[-90,90] or lon infinite
  RENDER_API ErrorType flyTo(double (&cameraOption)[11], int32_t duration = 0,
                             void (*frameCallback)(void*, double) = nullptr, void (*finishCallback)(void*) = nullptr,
                             void* userData = nullptr, double* bezierCoord = nullptr, int32_t bezierCoordLen = 0);

  // get a screen location that corresponds to a geographical coordinate (LatLng).
  // return ErrorType_InvalidPara if lat is out of range[-90,90] or lon infinite
  RENDER_API ErrorType getScrnCoordByLatLng(double lat, double lon, double& x, double& y);

  // get the geographic location that corresponds to a screen location.
  RENDER_API ErrorType getLatLngByScrnCoord(double x, double y, double& lat, double& lon);

  // get screen locations that corresponds to geographical coordinates if cameraOptions is set to parameters
  // in this function, the anchor of cameraOptions is meaningless.
  // cameraOption[0]~cameraOption[1]: center latitude, center longitude, nan for keeping unchanged
  // cameraOption[2]~cameraOption[5]: numbers of pixels from the top/left/botton/right edge, nan for keeping unchanged
  // cameraOption[6]~cameraOption[7]: anchorX, anchorY, nan for keeping unchanged
  // cameraOption[8]: zoom, nan for keeping unchanged
  // cameraOption[9]: bearing angle, nan for keeping unchanged
  // cameraOption[10]: pitch angle, nan for keeping unchanged
  // return ErrorType_InvalidPara if lat is out of range[-90,90] or lon infinite or arr is null or arrLen is less than
  // needed.
  RENDER_API ErrorType getScrnCoordByLatLng(double* latLons, int32_t latLonLen, double (&cameraOption)[11], double* coords,
                                 int32_t coordLen);
  
  
  // get geographical coordinates (LatLng) that corresponds (LatLng) to screen locations.
  // return ErrorType_InvalidPara if lat is out of range[-90,90] or lon infinite
  RENDER_API ErrorType getLatLngByScrnCoord(double* scrnCoords, int32_t coordLen, double (&cameraOption)[11], double* latLons, int32_t latLonLen);
  

  // get the LatLngBounds(sw latitude, sw longitude, ne latitude, ne longitude) that are centered on screen
  // at the greatest possible zoom level when the CameraOptions transforms the camera.
  RENDER_API ErrorType latLngBoundsForCamera(double (&cameraOption)[11], double (&bounds)[4]);

  // get center and zoom that transforms the camera such that the specified latitude/longitude bounds are centered on
  // screen at the greatest possible zoom level while maintaining current camera position bearing and EdgeInsets values.
  // bounds: (sw latitude, sw longitude, ne latitude, ne longitude)
  // edgeInset: numbers of pixels from the top/left/botton/right edge
  // return ErrorType_InvalidPara if lat is out of range[-90,90] or lon infinite
  RENDER_API ErrorType cameraForLatLngBounds(double (&bounds)[4], double (&edgeInsets)[4], double& lat, double& lon, double& zoom,
                                  double bearing = 0.0);

  // set base map style by style name
  // needAnimate Change Style add Fade Animate
  RENDER_API ErrorType applyMapStyle(const char* styleName = "Light", bool needAnimate = false);

  RENDER_API ErrorType applyColorStyle(const char* styleName = "", bool needAnimate = true);

  // set base map style by buffer
  RENDER_API ErrorType applyMapStyleFromBuffer(const char* buffer, int size);

  // gen image id
  RENDER_API ErrorType genImageID(char buffer[128]);

  // add a image
  // return ErrorType_InvalidPara if if width * height * 4 != srcDataLen
  RENDER_API ErrorType addImage(const char* id, int32_t width, int32_t height, float pixelRatio, uint8_t* srcData,
                     int32_t srcDataLen);

  // remove image which of id is the 'id' in the map's style.
  RENDER_API ErrorType removeImage(const char* imageId);

  // The max frame rate at which this render is rendered, but it can't excess the ability of device hardware.
  RENDER_API ErrorType setMaxFps(int32_t fps);

  // map stop render, method render is unvalid
  RENDER_API ErrorType setPause(bool value);

  // Render the map. Please invork in render thread
  RENDER_API ErrorType render(IRenderOptions options = {});
  
  // Render the map. Please invork in render thread
  // return true if current frame is valid,default is true.
  // return false if current frame isn't valid, and will not do glSwapbuffer. Only android
  RENDER_API bool render2(IRenderOptions options = {});

  // require to update map.
  RENDER_API ErrorType requireUpdate();

  RENDER_API ErrorType update();

  // get the height of map sky region in pixels.
  RENDER_API ErrorType getSkyHeight(int32_t& height);

  // get a tile image
  // return ErrorType_InvalidPara if dateLen is less than width * height * 4
  RENDER_API ErrorType readStillImage(int32_t width, int32_t height, int32_t cx, int32_t cy, uint8_t* data, int32_t dataLen, ICaptureOptions options = {});

  // reload base map data
  RENDER_API ErrorType reloadBaseSource();

  // reload source
  RENDER_API ErrorType reloadSource(const char* sourceID);

  // set debug tile border
  // return ErrorType_InvalidPara sourceID is nullptr
  RENDER_API ErrorType setDebugTileBorder(bool value, const char* sourceId = "sankuai");

  /// map observer callback
  ///@{
  // notify render, any thread
  RENDER_API ErrorType setOnUpdate(void (*callback)(void*), void* userData);

  // pre render in main thread
  RENDER_API ErrorType setOnSyncRenderThread(void (*callback)(void*), void* userData);

  // pre render in render thread
  RENDER_API ErrorType setOnRenderWill(void (*callback)(void*), void* userData);

  // render end in render thead,
  // If this callback occurs, the map will not refresh in the next frame
  RENDER_API ErrorType setOnRenderMapEnd(void (*callback)(void*), void* userData);

  // render partial end in render thead,
  // If this callback occurs, this means no tile is loading, all tiles is renderable,
  // but symbol maybe do placement
  RENDER_API ErrorType setOnPartialRenderMap(void (*callback)(void*), void* userData);

  // carmera will change in main thread
  RENDER_API ErrorType setOnCameraWillChange(void (*callback)(void*), void* userData);

  // carmera is changeing in main thread
  RENDER_API ErrorType setOnCameraIsChanging(void (*callback)(void*), void* userData);

  // carmera change finished in main thread
  RENDER_API ErrorType setOnCameraDidChange(void (*callback)(void*), void* userData);

  // style will load in main thread
  RENDER_API ErrorType setOnStyleWillLoad(void (*callback)(void*), void* userData);

  // style is loaded in main thread,
  // but this style has not been applied to the map
  RENDER_API ErrorType setOnStyleWillLoaded(void (*callback)(void*), void* userData);

  // style is loaded and applied to the map in main thread
  RENDER_API ErrorType setOnStyleLoaded(void (*callback)(void*, const char* styleUrl, StyleLoadingFlag styleLoadingFlag), void* userData);

  // style loaded error in main thread
  RENDER_API ErrorType setOnStyleLoadedError(void (*callback)(void*), void* userData);

  // first render in main thread,
  // this means at least one tile is rendered
  RENDER_API ErrorType setOnStyleFirstRender(void (*callback)(void*), void* userData);

  // tile will load in render thread
  ErrorType setOnTileWillLoad(void (*callback)(void*), void* userData);

  // tile is loaded in render thread
  ErrorType setOnTileLoaded(void (*callback)(void*), void* userData);

  // tile is loaded error in render thread
  ErrorType setOnTileLoadError(void (*callback)(void*), void* userData);

  // tile is loaded successfully(not including symbol)
  ErrorType setOnTileEvent(void (*callback)(void*, uint32_t x, uint32_t y, uint32_t z, int16_t wrap, int8_t overscaledZ,
                                            int32_t buildTime, int32_t flag),
                           void* userData);

  // raster tile is Internal or Foreign
  RENDER_API ErrorType setOnRasterForeignState(void (*callback)(void*,RasterStateFlag_), void* userData);
  /// @}

  /// query the map for rendered features
  /// @{
  // query the map screen point(screenXY[0], srceenXY[1]) for rendered features, get the handle of result features
  RENDER_API ErrorType queryRenderedFeaturesByOrder(double (&screenXY)[2], void (*callback)(FeaturesHandle, void*),
                                         void* userData = nullptr);

  // query the map screen box(screenXY[0], srceenXY[1])~(screenXY[2], srceenXY[3]) for rendered features, get the handle
  // of result features
  RENDER_API ErrorType queryRenderedFeaturesByOrder(double (&screenXY)[4], void (*callback)(FeaturesHandle, void*),
                                         void* userData = nullptr);

  [[deprecated]]
  RENDER_API ErrorType queryRenderedFeaturesByOrder(double (&screenXY)[2], FeaturesHandle& handle) {
    handle = 0;
    return ErrorType_None;
  }
  [[deprecated]]
  RENDER_API ErrorType queryRenderedFeaturesByOrder(double (&screenXY)[4], FeaturesHandle& handle) {
    handle = 0;
    return ErrorType_None;
  }
  [[deprecated]]
  RENDER_API ErrorType queryRenderedFeaturesByOrder(double* screenPoints, int32_t pointsLen, FeaturesHandle& handle) {
    handle = 0;
    return ErrorType_None;
  }

  // query the map screen point for screen ui, get the id of result screen ui(sorted by z axis)
  // x, y: screen coordinate, unit: dp, origin: left bottom
  // id: queryed id of screen ui, 0 if unqueryed
  RENDER_API ErrorType queryScreenUi(double x, double y, std::int32_t& id);

  // get the number of result features
  RENDER_API ErrorType getFeatureNum(FeaturesHandle handle, int32_t& num);

  // get featureType
  // FeatureTypeFlag: {FeatureTypeFlag_Point,FeatureTypeFlag_MultiPoint,FeatureTypeFlag_Line,FeatureTypeFlag_MultiLine,
  //                   FeatureTypeFlag_Polygon,FeatureTypeFlag_MultiPolygon}
  RENDER_API ErrorType getFeatureType(FeaturesHandle handle, int32_t featureInd, FeatureTypeFlag& type);

  // get the property value type
  // bool: FeaturePropertyType_Bool
  // int64_t: FeaturePropertyType_Long
  // double: FeaturePropertyType_Double
  // const char*: FeaturePropertyType_String
  // can't find the key or the value type is not supported to get: FeaturePropertyType_None
  RENDER_API ErrorType getFeaturePropertyType(FeaturesHandle handle, int32_t featureInd, const char* key,
                                   FeaturePropertyType& type);

  // get the properties of result features
  // if the type is not matched, return ErrorType_InvalidPara
  // if the length of char* value exceed 255, return ErrorType_InvalidPara
  // built-in properties:
  // key: maprender-sourcelayer          PropertyType: char (&value)[256]
  // key: render-style-sourcelayer       PropertyType: char (&value)[256]
  // key: render-style-sort-index        PropertyType: int64_t   only for tile render
  // key: render-style-feature-index     PropertyType: int64_t   only for no-tile render
  // key: related-feature-indexes        PropertyType: char (&value)[256].
  // key: id;                            PropertyType: char (&value)[256].
  // key: longitude;                     PropertyType: double    only for FeatureTypeFlag_Point
  // key: latitude;                      PropertyType: double    only for FeatureTypeFlag_Point
  RENDER_API ErrorType getFeatureProperty(FeaturesHandle handle, int32_t featureInd, const char* key, bool& value);
  RENDER_API ErrorType getFeatureProperty(FeaturesHandle handle, int32_t featureInd, const char* key, int64_t& value);
  RENDER_API ErrorType getFeatureProperty(FeaturesHandle handle, int32_t featureInd, const char* key, double& value);
  RENDER_API ErrorType getFeatureProperty(FeaturesHandle handle, int32_t featureInd, const char* key, char (&value)[256],
                               int32_t& valueLen);

  // destroy the queried result
  RENDER_API ErrorType destroyFeatures(FeaturesHandle handle);
  /// @}

  /// indoor activation
  /// @{
  // enable/disable indoor
  RENDER_API ErrorType setIndoor(bool value, bool supportOverview = false);

  // set indoor mask layer enable/disable
  RENDER_API ErrorType setIndoorMask(bool value);

  // set indoor mask layer color
  // color: rgba of the color, range:[0,1]
  RENDER_API ErrorType setIndoorMaskColor(float (&color)[4]);

  // Set building display floor
  // id - building featue id
  // floorname - one of "floornames"
  // floorNum - floornum corresponding to floorname
  RENDER_API ErrorType setIndoorFloor(int64_t id, const char* floorName, int32_t floorNum);

  // make building highlight
  // id - building feature id
  RENDER_API ErrorType addHighlightBuilding(int64_t id);

  // remove building hightlight
  // id - building feature id
  RENDER_API ErrorType removeHighlightBuilding(int64_t id);

  // remove all hightlight
  RENDER_API ErrorType removeHighlightBuilding();

  // callback for current indoor buildings
  RENDER_API ErrorType setOnIndoorBuildingsCallback(void (*callback)(FeaturesHandle, void*), void* userData = nullptr);

  RENDER_API ErrorType setIndoorQueryBox(float minX, float minY, float maxX, float maxY);
  
  // is enable indoor
  RENDER_API ErrorType getIndoor(bool& value);
  /// @}

  /// road traffic
  /// @{
  // enable/disable road traffic
  // for example :map-render/src/map-render-unit-test/test/dynamic_map.cpp---RoadTrafficUnitTest.
  RENDER_API ErrorType setRoadTraffic(bool value);

  // set road background color
  // for example :map-render/src/map-render-unit-test/test/dynamic_map.cpp---RoadTrafficUnitTest.
  RENDER_API ErrorType setRoadBackgroundColor(float (&color)[4]);

  // set road background casing color
  // for example :map-render/src/map-render-unit-test/test/dynamic_map.cpp---RoadTrafficUnitTest.
  RENDER_API ErrorType setRoadCasingColor(float (&color)[4]);

  // set traffic color
  // for example :map-render/src/map-render-unit-test/test/dynamic_map.cpp---RoadTrafficUnitTest.
  RENDER_API ErrorType setTrafficColor(TrafficLevel level, float (&color)[4]);

  // deprecated!!
  // set road source
  RENDER_API ErrorType setRoadSource(const char* source);

  // show base-map's road style or not when road traffic is enabled
  // for example :map-render/src/map-render-unit-test/test/dynamic_map.cpp---RoadTrafficUnitTest.
  RENDER_API ErrorType showRoadStyle(bool value);

  // set traffic style url. if styleUrl is "", the default style will be used.
  // note: It has a higher priority than setRoadBackgroundColor and setRoadCasingColor.
  // for example :map-render/src/map-render-unit-test/test/dynamic_map.cpp---RoadTrafficUnitTest.
  RENDER_API ErrorType setTrafficStyle(const char* styleUrl);

  // deprecated!!
  // use line traffic
  RENDER_API ErrorType setTrafficLineSource(bool value);
  
  // is enable road traffic
  RENDER_API ErrorType getRoadTraffic(bool& value);
  /// @}

  // show traffic light
  RENDER_API ErrorType showTrafficLight(bool value);

  // show 3d building
  RENDER_API ErrorType show3dBuilding(bool value);

  // show building
  RENDER_API ErrorType showBuilding(bool value);

  /// dynamic map
  /// @{
  // create dynamic map, if the style is existed, dynamic map will be updated
  RENDER_API ErrorType createOrUpdateDynamicMap(const char* style);
  RENDER_API ErrorType createOrUpdateDynamicMap(const char* style, const char* json);

  // destroy dynamic map
  // return ErrorType_InvalidPara if style is not existed
  RENDER_API ErrorType destroyDynamicMap(const char* style);

  // set dynamic map style
  // return ErrorType_InvalidPara if style is not existed
  RENDER_API ErrorType setDynamicMapGeoJSON(const char* style, const char* geojson);

  // set dynamic map style
  // return ErrorType_InvalidPara if style is not existed
  RENDER_API ErrorType addDynamicMapGeoJSON(const char* style, const char* key, const char* geojson, bool append = false);

  // set dynamic map style
  // size: feature size
  // return ErrorType_InvalidPara if style is not existed
  RENDER_API ErrorType addDynamicMapGeoJSONWithSize(const char* style, const char* key, const char* geojson, int32_t size, bool append = false);

  // remove dynamic map geojson
  // return ErrorType_InvalidPara if style is not existed
  RENDER_API ErrorType removeDynamicMapGeoJSON(const char* style, const char* key);

  // remove dynamic map geojson
  // return ErrorType_InvalidPara if style is not existed
  RENDER_API ErrorType removeDynamicMapGeoJSON(const char* style);

  // set dynamic map feature
  // return ErrorType_InvalidPara if style is not existed
  RENDER_API ErrorType setDynamicMapFeature(const char* style, int64_t id, const char* key, const char* value);

  // set dynamic map feature of specific geojson
  // return ErrorType_InvalidPara if style is not existed
  RENDER_API ErrorType setDynamicMapFeature(const char* style, const char* geojsonKey, int64_t id, const char* key,
                                 const char* value);
  
  // set dynamic map global feature
  RENDER_API ErrorType setGlobalDynamicMapFeature(const char* style, const char* geojsonKey, const char* key, const char* value);
  
  // reset dynamic map global feature, reset all global properties if key is nullptr(default value)
  RENDER_API ErrorType resetGlobalDynamicMapFeature(const char* style, const char* geojsonKey, const char* key = nullptr);

  // reset dynamic map feature
  // return ErrorType_InvalidPara if style is not existed
  RENDER_API ErrorType resetDynamicMapFeature(const char* style, int64_t id);

  // reset dynamic map feature of specific geojson, reset all properties if key is nullptr(default value)
  // return ErrorType_InvalidPara if style is not existed
  RENDER_API ErrorType resetDynamicMapFeature(const char* style, const char* geojsonKey, int64_t id, const char* key = nullptr);

  // reset dynamic map feature
  // return ErrorType_InvalidPara if style is not existed
  RENDER_API ErrorType resetDynamicMapFeatures(const char* style);

  // remove dynamic map feature of specific geojson
  // return ErrorType_InvalidPara if style is not existed
  RENDER_API ErrorType removeDynamicMapFeature(const char* style, const char* geojsonKey, int64_t id);

  // set dynamic map images
  // return ErrorType_InvalidPara if style is not existed
  RENDER_API ErrorType setDynamicMapImages(const char* style, const char* images[], int32_t imageCnt);

  // set callback for dynamic map
  // callback: called when dynamic map is loaded, style: dynamic style, ids: recorded ids
  // data: user data, transport to userdata of callback
  RENDER_API ErrorType setOnDynamicMapLoaded(const char* style,
                                  void (*callback)(void* userdata, const char* style, const int64_t* ids,
                                                   const int32_t len),
                                  void* userdata);

  // record dynamic map
  // style: dynamic map style
  // id: record id, eg:current timestamp
  RENDER_API ErrorType recordDynamicMap(const char* style, const int64_t id);

  /// @}

  /// layer
  /// @{
  // create a new layer and get a handle
  // return ErrorType_InvalidPara if layerId is existed
  RENDER_API ErrorType createLayer(const char* layerId, const char* sourceId, LayerHandle& layerHandle);

  // add source layer
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType setSourceLayer(LayerHandle handle, const char* sourceLayer);

  // set the layer visible/invisible
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType setLayerVisibility(LayerHandle handle, bool visible, const char* sublayer = nullptr);

  // set the layer order and ordertype
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType setLayerOrder(LayerHandle handle, float order, LayerOrderType orderType = LayerOrderType_Auto,
                          const char* sublayer = nullptr);
  
  // set the overlay layer order and ordertype
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType setOverlayLayerOrder(LayerHandle handle, float order, OverlayLayerOrderType overlayOrderType = OverlayLayerOrderType_SymbolAbove, const char* sublayer = nullptr);

  // set the min zoom the layer is visible
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType setLayerMinZoom(LayerHandle handle, float zoom, const char* sublayer = nullptr);

  // set the max zoom the layer is visible
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType setLayerMaxZoom(LayerHandle handle, float zoom, const char* sublayer = nullptr);

  // set interactive for layer, true is pickable,default value is true
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType setLayerInteractive(LayerHandle handle, bool interactive);

  // set layer property value
  // return ErrorType_InvalidPara if handle is invalid or the flag and the function type are not matched.
  RENDER_API ErrorType setLayerProperty(LayerHandle handle, LayerPropertyFlag flag, bool value, const char* sublayer = nullptr);
  RENDER_API ErrorType setLayerProperty(LayerHandle handle, LayerPropertyFlag flag, int32_t value, const char* sublayer = nullptr);
  RENDER_API ErrorType setLayerProperty(LayerHandle handle, LayerPropertyFlag flag, float value, const char* sublayer = nullptr);
  RENDER_API ErrorType setLayerProperty(LayerHandle handle, LayerPropertyFlag flag, float* value, int32_t valueLen,
                             const char* sublayer = nullptr);
  RENDER_API ErrorType setLayerProperty(LayerHandle handle, LayerPropertyFlag flag, const char* value,
                             const char* sublayer = nullptr);

  // set layer property by data driven
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType setLayerPropertyByDataDriven(LayerHandle handle, LayerPropertyFlag flag, const char* value,
                                         const char* sublayer = nullptr);

  // set properties with json
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType setLayerProperties(LayerHandle handle, const char* properties);

  // reset layer property to default
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType unsetLayerProperty(LayerHandle handle, LayerPropertyFlag flag, const char* sublayer = nullptr);
  RENDER_API ErrorType unsetLayerProperty(LayerHandle handle, const char* sublayer = nullptr);

  // add layer to map
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType addLayer(LayerHandle handle);

#ifdef SHENGTU
  void* getRenderStylePtr();
#endif

  // remove layer from map and destroy the handle
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType removeAndDestroyLayer(LayerHandle handle);

  // copy a new layer from the original layer
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType copyLayer(LayerHandle originLayerHandle, const char* layerId, const char* sourceId,
                      LayerHandle& newLayerHandle);
  /// @}

  /// geojsonSource and feature
  /// @{
  // create new source and get a handle
  // return ErrorType_InvalidPara if sourceId is existed
  RENDER_API ErrorType createGeojsonSource(const char* sourceId, GeojsonSourceHandle& geojsonHandle, bool lineMetrics = true,
                                ThreadModeFlag mode = ThreadMode_RenderThread, double tolerance = 0.375,
                                bool buildQueryIndex = true);

  // add geojson source to map
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType addGeojsonSource(GeojsonSourceHandle handle);

  // remove geojson source from map and destroy the handle
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType removeAndDestroyGeojsonSource(GeojsonSourceHandle handle);

  // set source url
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API   ErrorType setGeojsonSourceUrl(GeojsonSourceHandle handle, const char* url);

  // get sourceID for geojson handle
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType getGeojsonSourceID(GeojsonSourceHandle handle, char (&geojsonSourceID)[256]);

  // set imageref to geojsonsource
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType refImages(GeojsonSourceHandle handle, const char* images[], int32_t imageCnt);

  // set thread mode
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType setGeojsonSourceThreadMode(GeojsonSourceHandle handle, ThreadModeFlag mode);

  // the functions below to set features is incremental settings
  // set feature amount
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType setFeatureNum(GeojsonSourceHandle handle, int32_t num);

  // set feature
  // return ErrorType_InvalidPara if handle is invalid or featureInd is greater than or equal to fetureNum
  RENDER_API ErrorType setFeature(GeojsonSourceHandle handle, int32_t featureInd, FeatureTypeFlag flag, double* data,
                       int32_t dataLen, int32_t* startInd = nullptr, int32_t startIndLen = 0);

  // remove feature
  // return ErrorType_InvalidPara if handle is invalid or featureInd is greater than or equal to fetureNum
  RENDER_API ErrorType removeFeature(GeojsonSourceHandle handle, int32_t featureInd);

  // set feature property, if the key exists, the value will be replaced.
  // return ErrorType_InvalidPara if handle is invalid or featureInd is greater than or equal to fetureNum
  RENDER_API ErrorType addFeatureProperty(GeojsonSourceHandle handle, int32_t featureInd, const char* key, bool value);
  RENDER_API ErrorType addFeatureProperty(GeojsonSourceHandle handle, int32_t featureInd, const char* key, double value);
  RENDER_API ErrorType addFeatureProperty(GeojsonSourceHandle handle, int32_t featureInd, const char* key, double* value,
                               int32_t valueLen);
  RENDER_API ErrorType addFeatureProperty(GeojsonSourceHandle handle, int32_t featureInd, const char* key, int64_t* value,
                               int32_t valueLen);
  RENDER_API ErrorType addFeatureProperty(GeojsonSourceHandle handle, int32_t featureInd, const char* key, const char* value);
  
  RENDER_API ErrorType addFeatureProperty(GeojsonSourceHandle handle, int32_t featureInd, const char* key, const char* value[], int32_t valueLen);

  // set features from featureHandle
  RENDER_API ErrorType setFeatures(GeojsonSourceHandle handle, FeaturesHandle featureHandle, bool clearGeoJSON, bool destoryFeatureHandle);
  
  // set auto merge line property key
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType setAutoMergePropertyKey(GeojsonSourceHandle handle, const char* propertyName);
  /// @}

  /// image source
  /// @{
  // create a new image source and get a handle
  // latLonArr: the lat/lon of four vertices, {lat1,lon1,lat2,lon2,lat3,lon3,lat4,lon4}
  // return ErrorType_InvalidPara if imageId is existed or lat is out of range[-90,90] or lon is nan or infinite
  RENDER_API ErrorType createImageSource(const char* sourceId, double (&latLonArr)[8], ImageSourceHandle& imageHandle);

  // add imageSource to map
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType addImageSource(ImageSourceHandle handle);

  // remove imageSource from map and destroy the handle
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType removeAndDestroyImageSource(ImageSourceHandle handle);

  // set vertex coordinates of image to imageSource
  // latLonArr: the lat/lon of four vertices, {lat1,lon1,lat2,lon2,lat3,lon3,lat4,lon4}
  // return ErrorType_InvalidPara if handle is invalid or lat is out of range[-90,90] or lon is nan or infinite
  RENDER_API ErrorType setImageCoord(ImageSourceHandle handle, double (&latLonArr)[8]);

  // set image to imageSource
  // return ErrorType_InvalidPara if handle is invalid or width * height * 4 != srcDataLen
  RENDER_API ErrorType setImage(ImageSourceHandle handle, int32_t width, int32_t height, float pixelRatio, uint8_t* srcData,
                     int32_t srcDataLen);
  /// @}

  /// raster source
  /// @{
  // create a new raster source and get a handle
  RENDER_API ErrorType createRasterSource(const char* rasterId, const char* url, int32_t tileSize, RasterSourceHandle& handle,  unsigned int minRange=0, unsigned int maxRange=22);

  // add rasterSource to map
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType addRasterSource(RasterSourceHandle handle);

  // remove rasterSource from map and destroy the handle
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType removeAndDestroyRasterSource(RasterSourceHandle handle);
  /// @}

  /// vaild foregin raster tile
  /// @{
  // enable/disable foregin raster tile
  // for example :map-render/src/map-render-unit-test/test/dynamic_map.cpp---RoadTrafficUnitTest.
  RENDER_API ErrorType setRasterForeign(bool value);
  
  // enable/disable foregin vector tile
  RENDER_API ErrorType setVectorForeign(bool value);

  /// arrow
  /// @{
  // create a new arrow group(contains one or more arrows) and get a handle, arrows will be add to map automatically.
  // mode: {ThreadMode_MultiThread, ThreadMode_CustomThread, ThreadMode_RenderThread}
  RENDER_API ErrorType createAndAddArrow(float width, ArrowHandle& handle, ThreadModeFlag mode = ThreadMode_RenderThread);

  // remove arrows from map and destroy the handle
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType removeAndDestroyArrow(ArrowHandle handle);

  // set arrow amount
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType setArrowFeatureNum(ArrowHandle handle, int num);

  // set arrow feature
  // return ErrorType_InvalidPara if handle is invalid or featureInd is greater than or equal to fetureNum
  RENDER_API ErrorType setArrowFeature(ArrowHandle handle, int featureInd, double* lonLat, int lonLatLen);

  // set arrow width
  RENDER_API ErrorType setArrowWidth(ArrowHandle handle, float width);

  // set arrow layer property value
  // return ErrorType_InvalidPara if handle is invalid or the flag and the function type are not matched.
  RENDER_API ErrorType setArrowLayerProperty(ArrowHandle handle, LayerPropertyFlag flag, bool value);
  RENDER_API ErrorType setArrowLayerProperty(ArrowHandle handle, LayerPropertyFlag flag, int value);
  RENDER_API ErrorType setArrowLayerProperty(ArrowHandle handle, LayerPropertyFlag flag, float value);
  RENDER_API ErrorType setArrowLayerProperty(ArrowHandle handle, LayerPropertyFlag flag, float* value, int valueLen);
  RENDER_API ErrorType setArrowLayerProperty(ArrowHandle handle, LayerPropertyFlag flag, const char* value);

  // set the arrow layer order and ordertype
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType setArrowLayerOrder(ArrowHandle handle, float order, LayerOrderType orderType = LayerOrderType_Auto,
                               const char* sublayer = nullptr);

  // set the arrow overlay layer order and ordertype
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType setArrowOverlayLayerOrder(LayerHandle handle, float order, OverlayLayerOrderType overlayOrderType = OverlayLayerOrderType_SymbolAbove,
                                                 const char* sublayer = nullptr);

  // set the arrow visible/invisible
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType setArrowLayerVisibility(ArrowHandle handle, bool visible, const char* sublayer = nullptr);

  // set the min zoom the arrow layer is visible
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType setArrowLayerMinZoom(ArrowHandle handle, float zoom, const char* sublayer = nullptr);

  // set the max zoom the arrow layer is visible
  // return ErrorType_InvalidPara if handle is invalid
  RENDER_API ErrorType setArrowLayerMaxZoom(ArrowHandle handle, float zoom, const char* sublayer = nullptr);

  // set tile cache type for sourceID
  // sourceID: source id. For example "sankuai"  "sankuai-traffic-source"
  // cacheType: cache type.
  RENDER_API ErrorType setTileCacheType(const char* sourceID, TileCacheType cacheType);

  // set tile cache ratio
  // sourceID: source id.
  // cacheRatio : [0, 1].
  RENDER_API ErrorType setTileCacheRatio(const char* sourceID, float cacheRatio);

  /// road crossing
  /// @{
  // create road crossing
  // note: The maximum pitch is changed (89.9 degree) when creating RoadCrossing!!!
  RENDER_API ErrorType createRoadCrossing(const char* style);

  // destroy road crossing
  RENDER_API ErrorType destroyRoadCrossing();

  // set crossing id,
  RENDER_API ErrorType setRoadCrossingID(const char* id);

  // get crossing id
  RENDER_API ErrorType getRoadCrossingID(char (&roadCrossID)[512]);

  // get crossing style url
  RENDER_API ErrorType getRoadCrossingStyleUrl(char (&roadCrossStyle)[1024]);

  /// @}

  /// screen ui
  /// @{
  // create or set image, if id is existed, set image again, init size: 1dp x 1dp, scale if needed, origin: left bottom
  // id: out, id of created or updated screen ui
  // matrix: in, matrix for rotate, scale, translate, can be generated by getMatrix
  // imageID: in, image name
  // uv_lb: in, left and bottom of texture coordinate, range: 0~1
  // ub_rt: in, right and top of texture coordinate, range:0~1
  // color: in, mix color
  RENDER_API ErrorType createOrSetScreenImage(std::int32_t& id, float (&matrix)[16], const char* imageID, float (&uv_lb)[2],
                                   float (&uv_rt)[2], float (&color)[4]);

  RENDER_API ErrorType removeScreenImage(std::int32_t id);

  /// @}

  /// @{
  /// enabl or disable road block
  RENDER_API ErrorType setRoadBlock(bool value);
  /// @}

  /// @{
  // get map's max pitch angle
  RENDER_API ErrorType getMaxPitch(double& maxPitch);

  // get map's min pitch angle
  RENDER_API ErrorType getMinPitch(double& minPitch);
  /// @}

  /// weather
  /// @{
  // enable show weather effect
  RENDER_API ErrorType setWeatherType(WeatherType weatherType);

  // disable weather effect
  RENDER_API ErrorType disableWeather();

  // update intensity for WeatherType_Hot_Distortion or WeatherType_Hot
  // intensity: is valid for [0,1], 0 is disable distortion, default is 0.2.
  RENDER_API ErrorType setWeatherIntensity(float intensity);

  // enable/disable auto update for weather. default is false.
  RENDER_API ErrorType setWeatherAutoUpdate(bool autoUpdate);
  
  RENDER_API ErrorType setWeatherOrder(float order, OverlayLayerOrderType overlayOrderType = OverlayLayerOrderType_SymbolAbove);

  /// @}

  // output func call record list
  RENDER_API ErrorType outputFuncCallRecordList(char (&output)[12 * 1024]);

  RENDER_API ErrorType onLowMemory();

  // set preload parent tile level, default 0 (0-4)
  RENDER_API ErrorType setPreloadParentTileLevel(int level);

  // refresh frame always if v = true
  RENDER_API  ErrorType refreshFrame(bool);

  RENDER_API ErrorType getRenderFrameNum(uint64_t& frameNum);

  /// custom layer
  /// @{
  using CustomLayerOnInit = void(*) (const LayerHandle&, void*);
  // params[0]:     width
  // params[1]:     height
  // params[2]:     latitude
  // params[3]:     longitude
  // params[4]:     zoom
  // params[5]:     bearing
  // params[6]:     pitch
  // params[7]:     fieldOfView
  // params[8~10]:  eyePosition
  // params[11~26]: viewMatrix
  // params[27~42]: projectionMatrix
  using CustomLayerOnDraw = void(*) (const LayerHandle&, const double(&params)[43], void*);

  RENDER_API ErrorType createCustomLayer(const char* layerId, const char* sourceId, LayerHandle& layerHandle,
                              CustomLayerOnInit onInit,
                              CustomLayerOnDraw onDraw,
                              void* userData = nullptr);
  /// @}

  // set request offline tile data cache callback
  RENDER_API ErrorType setRequestOfflineTileDataCallback(void (*finishCallback)(void*, int64_t handle, bool suf, const char* rst, int32_t len),
                                                         void* userData = nullptr);

  // request offline tile data cache
  RENDER_API ErrorType requestOfflineTileData(int64_t& handle, const char* tileUrl, float pixelRatio,
                                              int32_t x, int32_t y, int8_t z, int8_t overz,
                                              bool abroad = false, int32_t abroad_level = 7,
                                              TilesetScheme_ scheme = TilesetScheme_::XYZ);

  // set debug tile state
  // if set true, no tile area will display red, tile background will display green.
  RENDER_API static ErrorType setDebugTileState(bool value);

  // clear offline data cache
  RENDER_API static ErrorType clearOfflineData(const char* dbDir);

  // clear offline data cache
  RENDER_API static ErrorType clearPartOfflineData(const char* dbDir, uint64_t keepCacheSize);

  // add a new map style
  RENDER_API static ErrorType addStyleUrl(const char* styleName, const char* url);

  // remove a style
  RENDER_API static ErrorType removeStyleUrl(const char* styleName);

  // set online request hoost type
  // HostType: HostType_Prod = 0, HostType_Stage = 1, HostType_Prod_HK_Macao = 2
  RENDER_API static ErrorType setHostType(HostType hostType);

  // get online request hoost type
  // HostType: HostType_Prod = 0, HostType_Stage = 1, HostType_Prod_HK_Macao = 2
  RENDER_API static ErrorType getHostType(HostType& hostType);

  // add a base url
  RENDER_API static ErrorType addBaseUrl(const char* token, const char* url);

  // add url parameter
  RENDER_API static ErrorType addUrlParameters(const char* paraName, const char* paraValue);

  // get all default style names, ex: "Light;Dark;Terrain"
  RENDER_API static ErrorType getDefaultStylesName(char (&names)[1024]);
  /// util
  /// @{
  // get merator coordinate from latlon
  // return ErrorType_InvalidPara if lat is out of range[-90,90] or lon is nan or infinite
  RENDER_API static ErrorType projectedMetersForLatLng(double lat, double lon, double& northing, double& easting);

  // get latlon from merator coordinate
  RENDER_API static ErrorType latLngForProjectedMeters(double northing, double easting, double& lat, double& lon);

  // get meters per pixel at latitude
  // return ErrorType_InvalidPara if lat is out of range[-90,90]
  RENDER_API static ErrorType getMetersPerPixelAtLatitude(double lat, double zoom, double& meters);

  // get meters per pixel
  RENDER_API static ErrorType getProjectedMetersPerPixel(double zoom, double& meters);

  // get Mercator deformation ratio
  RENDER_API static ErrorType getMercatorRatio(double lat, double& ratio);

  // get screen coordinate from latlon
  // return ErrorType_InvalidPara if lat is out of range[-90,90] or lon is nan or infinite
  RENDER_API static ErrorType project(double lat, double lon, double zoom, double& x, double& y);

  // get latlon from screen coordinate
  RENDER_API static ErrorType unproject(double x, double y, double zoom, double& lat, double& lon);

  // get the boundary coordinates of the hexagon where the specifical point is located (LatLng).
  // return ErrorType_InvalidPara if lat is out of range[-90,90] or lon infinite
  RENDER_API static ErrorType getHexagonBoundsByLatLng(double lat, double lon, double size, double gap, double (&bounds)[12],
                                            double centerLat = 0.0);

  // get version
  RENDER_API static ErrorType getVersion(char (&version)[32], int32_t& versionLen);

  // set version
  RENDER_API static ErrorType setVersion(char (&version)[32], int32_t& versionLen);

  // check version by condition list. (The condition rules follow podfile version control rules)
  // condition is split by ';' like "1.1118.9;1.1119.1;> 1.1118.0;< 1.1119.400;~> 1.1118;"
  // if one condition is considered return true, else return false
  RENDER_API static bool checkVersion(const char* condition_list);

  // get matrix: scale->rotation->translation
  // 1. scale
  // 2. rotate about x, y and z axis by given angle at a given anchor point
  // 3. translate the corresponding distance on the x, y and z axis from anchor
  //
  // anchor: float[3], the position of the anchor point, relative to the origin of the screen ui, unit:dp
  // rotation: float[3], angle for rotation about x, y, z axis, direction: counterclockwise, unit: radian
  // scale: float[3], scale ratio for x, y and z, range: >=0
  // translation: float[3], origin: anchor, direction: x->right, y->up, z->0 for 2D screen, unit:dp
  RENDER_API static ErrorType getMatrix(float (&matrix)[16], const float (&anchor)[3], const float (&rotation)[3],
                             const float (&scale)[3], const float (&translation)[3]);

  // get base-map style num
  RENDER_API static ErrorType getBaseStyleNum(int& num);

  // get base-map style name for index
  RENDER_API static ErrorType getBaseStyleName(int index, char (&styleName)[256]);

  // get base-map style's url for styleName
  RENDER_API static ErrorType getBaseStyleUrl(const char* styleName, char (&url)[1024]);

  // get global max pitch angle
  RENDER_API static ErrorType getGlobalMaxPitch(double& maxPitch);

  // get global min pitch angle
  RENDER_API static ErrorType getGlobalMinPitch(double& minPitch);

  // get spherical distance, unit: meter
  RENDER_API  static ErrorType getSphericalDistance(const double (&latLonArr)[4], double& distance);

  // return true if point inside polygon
  RENDER_API static ErrorType checkPolygonContainsPoint(const double* polygon, int32_t polygonLen, const double (&point)[2],
                                             bool& value);

  // set global PerformanceLog Switch
  // type: PerformanceLogType (FPS, TileLife...)
  // value: true(open), false(close)
  RENDER_API static ErrorType setPerformanceLogSwitch(PerformanceLogType type, bool value);
  
  // get the calling thread's last-error log
  RENDER_API static void getLastError(char (&output)[1024]);

  // only used for IOS
  static ErrorType wrap(double value, double min, double max, double& out);

  /// @}

  const IMapPrivate* getIMapPrivate() const;
 private:
  struct Imp;
  Imp* imp = nullptr;

  static bool isLatLngValid(double lat, double lon);

  ErrorType refreshTrafficLightState(void* style);

  ErrorType refreshBuildingState(void* style);
};
}  // namespace mdgl

#endif
