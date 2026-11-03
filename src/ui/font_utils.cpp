// Aseprite UI Library
// Copyright (C) 2026  Igara Studio S.A.
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include "ui/font_utils.h"

#include <algorithm>
#include <cmath>

namespace ui {

static bool g_useFallbackMetrics = false;

void setUseFallbackMetrics(bool state)
{
  g_useFallbackMetrics = state;
}

bool useFallbackMetrics()
{
  return g_useFallbackMetrics;
}

int MergedMetrics::height() const
{
  return int(std::ceil(descent - ascent));
}

MergedMetrics mergedMetrics(const text::FontRef& font)
{
  text::FontMetrics m;
  font->metrics(&m);
  MergedMetrics result{ m.ascent, m.descent };

  if (!g_useFallbackMetrics)
    return result;

  for (text::FontRef f = font->fallback(); f; f = f->fallback()) {
    text::FontMetrics fm;
    f->metrics(&fm);
    result.ascent = std::min(result.ascent, fm.ascent);
    result.descent = std::max(result.descent, fm.descent);
  }
  return result;
}

int mergedLineHeight(const text::FontRef& font)
{
  int h = int(std::ceil(font->lineHeight()));
  if (!g_useFallbackMetrics)
    return h;

  for (text::FontRef f = font->fallback(); f; f = f->fallback())
    h = std::max(h, int(std::ceil(f->lineHeight())));
  return h;
}

} // namespace ui
