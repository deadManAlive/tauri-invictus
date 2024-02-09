#include "LookAndFeel.h"
#include <utility>

PanLook::PanLook(Origin origin, Channel channel, bool reversed)
    : sliderOrigin(origin)
    , sliderChannel(channel)
    , isReversed(reversed)
{   
}

PanLook::PanLook(Origin origin, bool reversed)
    : sliderOrigin(origin)
    , isReversed(reversed)
{
}

Colour PanLook::leftColour = Colours::goldenrod;
Colour PanLook::rightColour = Colours::indianred;
Colour PanLook::thumbColour = Colours::bisque;

void PanLook::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider) {
    const auto outline = slider.findColour (Slider::rotarySliderOutlineColourId);

    Colour fill;
    float fillOriginAngle;

    if (sliderOrigin == Origin::FromMid) {
        fill = sliderPos > 0.5f ? rightColour : leftColour;
        fillOriginAngle = MathConstants<float>::twoPi;
    } else {
        fill = rightColour;
        fillOriginAngle = rotaryStartAngle;
    }

    const auto bounds = Rectangle<int> (x, y, width, height).toFloat().reduced (10);

    const auto radius = jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
    const auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    const auto lineW = jmin (8.0f, radius * 0.25f);
    const auto arcRadius = radius - lineW * 0.5f;

    Path backgroundArc;
    backgroundArc.addCentredArc (bounds.getCentreX(),
                                 bounds.getCentreY(),
                                 arcRadius,
                                 arcRadius,
                                 0.0f,
                                 rotaryStartAngle,
                                 rotaryEndAngle,
                                 true);

    g.setColour (outline);
    g.strokePath (backgroundArc, PathStrokeType (lineW, PathStrokeType::mitered, PathStrokeType::butt));

    if (slider.isEnabled())
    {
        Path valueArc;
        valueArc.addCentredArc (bounds.getCentreX(),
                                bounds.getCentreY(),
                                arcRadius,
                                arcRadius,
                                0.0f,
                                fillOriginAngle,
                                toAngle,
                                true);

        g.setColour (fill);
        g.strokePath (valueArc, PathStrokeType (lineW, PathStrokeType::mitered, PathStrokeType::butt));
    }

    Path thumbArc;

    const auto thumbArcStartAngle = toAngle - 0.1f;
    const auto thumbArcEndAngle = toAngle + 0.1f;
    
    thumbArc.addCentredArc(bounds.getCentreX(),
                           bounds.getCentreY(),
                           arcRadius - lineW * 1.5f,
                           arcRadius - lineW * 1.5f,
                           0.f,
                           thumbArcStartAngle,
                           thumbArcEndAngle,
                           true);

    g.setColour(thumbColour);
    g.strokePath(thumbArc, PathStrokeType(4.f * lineW, PathStrokeType::mitered, PathStrokeType::butt));
}

void PanLook::drawLinearSlider(Graphics& g,
                               int x,
                               int y,
                               int width,
                               int height,
                               float sliderPos,
                               float minSliderPos,
                               float maxSliderPos,
                               Slider::SliderStyle style,
                               Slider& slider) {
    
    auto trackWidth = jmin (8.0f, slider.isHorizontal() ? (float) height * 0.25f : (float) width * 0.25f);
    
    Point<float> startPoint (slider.isHorizontal() ? (float) x : (float) x + (float) width * 0.5f,
                             slider.isHorizontal() ? (float) y + (float) height * 0.5f : (float) (height + y));
    Point<float> endPoint (slider.isHorizontal() ? (float) (width + x) : startPoint.x,
                           slider.isHorizontal() ? startPoint.y : (float) y);

    if (isReversed) {
        std::swap(startPoint, endPoint);
    }

    Point<float> midPoint(slider.isHorizontal() ? (float) (x + width * 0.5) : startPoint.x,
                          slider.isHorizontal() ? startPoint.y : (float) (y + height * 0.5));
    Point<float> thumbPoint(slider.isHorizontal() ? sliderPos : startPoint.x,
                            slider.isHorizontal() ? startPoint.y : sliderPos);

    Path backgroundTrack;
    backgroundTrack.startNewSubPath(startPoint);
    backgroundTrack.lineTo(endPoint);
    g.setColour(slider.findColour(Slider::backgroundColourId));
    g.strokePath(backgroundTrack, {trackWidth, PathStrokeType::mitered, PathStrokeType::butt});

    const auto fill = sliderChannel == Channel::Left ? leftColour : rightColour;

    Path valueTrack;
    if (sliderOrigin == Origin::FromMin) {
        valueTrack.startNewSubPath(startPoint);
    } else {
        valueTrack.startNewSubPath(midPoint);
    }
    valueTrack.lineTo(thumbPoint);
    g.setColour(fill);
    g.strokePath(valueTrack, {trackWidth, PathStrokeType::mitered, PathStrokeType::butt});

    Path thumbTrack;

    const auto hoffset = jmin(8.f, (float) width * 0.02f);
    // Point<float> thumbStartPoint(startPoint.x, thumbPoint.y - (float)height * 0.02f);
    Point<float> thumbStartPoint(slider.isHorizontal() ? thumbPoint.x - hoffset : startPoint.x,
                                 slider.isHorizontal() ? startPoint.y : thumbPoint.y - (float) height * 0.02f);
    // Point<float> thumbEndPoint(startPoint.x, thumbPoint.y + (float)height * 0.02f);
    Point<float> thumbEndPoint(slider.isHorizontal() ? thumbPoint.x + hoffset : startPoint.x,
                               slider.isHorizontal() ? startPoint.y : thumbPoint.y + (float) height * 0.02f);

    thumbTrack.startNewSubPath(thumbStartPoint);
    thumbTrack.lineTo(thumbEndPoint);
    g.setColour(thumbColour);
    g.strokePath(thumbTrack, {2 * trackWidth, PathStrokeType::mitered, PathStrokeType::butt});

    ignoreUnused(minSliderPos, maxSliderPos, style);
}