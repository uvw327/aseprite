// Aseprite UI Library
// Copyright (C) 2026  Igara Studio S.A.
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef UI_FONT_UTILS_H_INCLUDED
#define UI_FONT_UTILS_H_INCLUDED
#pragma once

#include "text/font.h"
#include "text/font_metrics.h"

namespace ui {

// When the current UI language needs taller glyphs than the main font
// (e.g. Chinese/Japanese/Korean fallback fonts), widgets must size and
// center their text using the merged metrics of the font + fallback chain.
// English (and any language without a taller fallback) keeps the classic
// behavior: only the main font metrics are used.
void setUseFallbackMetrics(bool state);
bool useFallbackMetrics();

struct MergedMetrics {
  float ascent;  // negative
  float descent; // positive

  int height() const;
};

MergedMetrics mergedMetrics(const text::FontRef& font);
int mergedLineHeight(const text::FontRef& font);

} // namespace ui

#endif
