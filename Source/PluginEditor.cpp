#include "PluginEditor.h"
#include <BinaryData.h>
void PanelLook::drawRotarySlider(juce::Graphics& g,int x,int y,int w,int h,float pos,float start,float end,juce::Slider&) {
 auto r=juce::Rectangle<float>((float)x,(float)y,(float)w,(float)h).reduced(5);
 auto c=r.getCentre(); const auto radius=juce::jmin(r.getWidth(),r.getHeight())/2;
 g.setColour(juce::Colours::black.withAlpha(0.22f));g.fillEllipse(r.translated(1,3));
 g.setGradientFill(juce::ColourGradient(juce::Colour(0xff45494d),r.getTopLeft(),juce::Colour(0xff101214),r.getBottomRight(),false));g.fillEllipse(r);
 g.setColour(juce::Colour(0xff070809));g.drawEllipse(r,2);
 g.setColour(juce::Colour(0xff62666a));g.drawEllipse(r.reduced(5),1);
 const auto angle=start+pos*(end-start);
 auto p=c+juce::Point<float>(std::sin(angle),-std::cos(angle))*radius*0.82f;
 auto q=c+juce::Point<float>(std::sin(angle),-std::cos(angle))*radius*0.53f;
 g.setColour(juce::Colours::white);g.drawLine({p,q},4);
}
void PanelLook::drawToggleButton(juce::Graphics& g,juce::ToggleButton& b,bool hover,bool down) {
 auto r=b.getLocalBounds().toFloat().reduced(3);
 auto on=b.getToggleState();
 g.setColour(juce::Colours::black);g.fillEllipse(r);
 g.setGradientFill(juce::ColourGradient(on?juce::Colour(0xffccffad):juce::Colour(0xff51575b),r.getTopLeft(),on?juce::Colour(0xff4eb936):juce::Colour(0xff171b1d),r.getBottomRight(),false));
 g.fillEllipse(r.reduced(3));
 g.setColour((hover||down||b.hasKeyboardFocus(true))?juce::Colours::white:juce::Colour(0xff888888));g.drawEllipse(r.reduced(3),1.5f);
}
void RecallKnob::mouseDoubleClick(const juce::MouseEvent&) {
 auto editor=std::make_unique<juce::TextEditor>();
 editor->setSize(145,32);editor->setText(getTextFromValue(getValue()));editor->selectAll();
 auto* input=editor.get();juce::Component::SafePointer<RecallKnob> safe(this);
 input->onReturnKey=[safe,input]{if(safe){juce::Slider::ScopedDragNotification gesture(*safe);safe->setValue(safe->getValueFromText(input->getText()),juce::sendNotificationSync);}if(auto* box=input->findParentComponentOfClass<juce::CallOutBox>())box->dismiss();};
 input->onEscapeKey=[input]{if(auto* box=input->findParentComponentOfClass<juce::CallOutBox>())box->dismiss();};
 juce::CallOutBox::launchAsynchronously(std::move(editor),getScreenBounds(),nullptr);
 input->grabKeyboardFocus();
}
RecallEditor::RecallEditor(RecallProcessor& p):AudioProcessorEditor(p),panel(juce::ImageCache::getFromMemory(BinaryData::frontpanel_png,BinaryData::frontpanel_pngSize)) {
 setLookAndFeel(&look);addAndMakeVisible(controls);
 controls.setSize(706,1222);
 for(size_t i=0;i<knobs.size();++i) {
  auto& k=knobs[i];const auto& s=recall::specs[i];
  controls.addAndMakeVisible(k);k.setName(s.name);k.setTitle(s.name);
  k.setSliderStyle(juce::Slider::RotaryVerticalDrag);k.setTextBoxStyle(juce::Slider::NoTextBox,false,0,0);
  k.setRotaryParameters(juce::degreesToRadians(210.0f),juce::degreesToRadians(510.0f),true);
  k.setPopupDisplayEnabled(true,true,this);
  k.setTooltip(juce::String(s.name)+": Ziehen / Mausrad · Shift: fein · Doppelklick: Wert eingeben");
  k.setVelocityBasedMode(false);k.setMouseDragSensitivity(250);
  k.setBounds(juce::roundToInt(s.x-66),juce::roundToInt(s.y-66),132,132);
  sliders[i]=std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(p.state,s.id,k);
 }
 for(size_t i=0;i<3;++i){auto& b=buttons[i];controls.addAndMakeVisible(b);b.setName(recall::toggleNames[i]);b.setTitle(recall::toggleNames[i]);b.setTooltip(recall::toggleNames[i]);b.setBounds(288,777+(int)i*147,66,66);toggles[i]=std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(p.state,recall::toggleIDs[i],b);}
 setResizable(true,true);getConstrainer()->setFixedAspectRatio(706.0/1256.0);
 setResizeLimits(353,628,847,1507);setSize(494,879);
}
RecallEditor::~RecallEditor(){setLookAndFeel(nullptr);}
void RecallEditor::resized(){controls.setTransform(juce::AffineTransform::scale((float)getWidth()/706.0f));}
void RecallEditor::paint(juce::Graphics& g){
 g.fillAll(juce::Colour(0xff202428));const auto scale=(float)getWidth()/706.0f;
 g.drawImage(panel,juce::Rectangle<float>(0,0,(float)getWidth(),1222*scale));
 g.setColour(juce::Colour(0xffdddddd));g.setFont(12*scale);
 g.drawText("KOENICH RECALL  /  elysia xMax  /  V1.0.2",0,juce::roundToInt(1224*scale),getWidth(),juce::roundToInt(30*scale),juce::Justification::centred);
}
