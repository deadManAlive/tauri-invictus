#pragma once

#include <JuceHeader.h>

class PanLook : public LookAndFeel_V4 {
public:
    //==============================================================================
    enum class Origin {
        FromMin,
        FromMid,
    };

    enum class Channel {
        Left,
        Right,
    };

    //==============================================================================
    PanLook() = delete;
    PanLook(Origin, bool = false);
    PanLook(Origin, Channel, bool = false);

    void drawRotarySlider(Graphics&, int, int, int, int, float, float, float, Slider&) override;
    void drawLinearSlider(Graphics&, int, int, int, int, float, float, float, Slider::SliderStyle, Slider&) override;
    
    //==============================================================================
    static Colour leftColour;
    static Colour rightColour;
    static Colour thumbColour;
private:
    Origin sliderOrigin;
    Channel sliderChannel;
    bool isReversed;
};