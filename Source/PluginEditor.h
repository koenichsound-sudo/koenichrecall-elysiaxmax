#pragma once
#include "PluginProcessor.h"
class PanelLook final : public juce::LookAndFeel_V4 {
public:
 void drawRotarySlider(juce::Graphics&,int,int,int,int,float,float,float,juce::Slider&) override;
 void drawToggleButton(juce::Graphics&,juce::ToggleButton&,bool,bool) override;
};
class RecallKnob final : public juce::Slider {
public:
 void mouseDrag(const juce::MouseEvent& e) override { setMouseDragSensitivity(e.mods.isShiftDown()?2000:250); juce::Slider::mouseDrag(e); }
 void mouseDoubleClick(const juce::MouseEvent&) override;
};
class RecallEditor final : public juce::AudioProcessorEditor {
public:
 explicit RecallEditor(RecallProcessor&);
 ~RecallEditor() override;
 void paint(juce::Graphics&) override;
 void resized() override;
private:
 PanelLook look;
 juce::Image panel;
 juce::Component controls;
 std::array<RecallKnob,12> knobs;
 std::array<juce::ToggleButton,3> buttons;
 std::array<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>,12> sliders;
 std::array<std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>,3> toggles;
 juce::TooltipWindow tooltip{this,600};
 JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RecallEditor)
};
