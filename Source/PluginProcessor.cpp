#include "PluginProcessor.h"
#include "PluginEditor.h"
RecallProcessor::RecallProcessor()
 : AudioProcessor(BusesProperties().withInput("Input",juce::AudioChannelSet::stereo(),true).withOutput("Output",juce::AudioChannelSet::stereo(),true)),
 state(*this,nullptr,"KoenichXMaxState",makeParameters()) {}
juce::AudioProcessorValueTreeState::ParameterLayout RecallProcessor::makeParameters() {
 juce::AudioProcessorValueTreeState::ParameterLayout layout;
 for(const auto& s:recall::specs)
  layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{s.id,1},s.name,recall::range(s),s.initial,
   juce::AudioParameterFloatAttributes().withLabel(s.unit).withStringFromValueFunction([s](float v,int){return juce::String(v,s.step<1?1:0)+s.unit;}).withValueFromStringFunction([](const juce::String& t){return t.getFloatValue();})));
 for(size_t i=0;i<3;++i) layout.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{recall::toggleIDs[i],1},recall::toggleNames[i],false));
 return layout;
}
bool RecallProcessor::isBusesLayoutSupported(const BusesLayout& l) const {
 const auto in=l.getMainInputChannelSet();
 return !in.isDisabled() && in==l.getMainOutputChannelSet() && in.size()<=64;
}
void RecallProcessor::getStateInformation(juce::MemoryBlock& dest) {
 auto tree=state.copyState(); tree.setProperty("version",1,nullptr);
 if(auto xml=tree.createXml()) copyXmlToBinary(*xml,dest);
}
void RecallProcessor::setStateInformation(const void* data,int bytes) {
 if(auto xml=getXmlFromBinary(data,bytes))
  if(xml->hasTagName(state.state.getType())) {
   auto incoming=juce::ValueTree::fromXml(*xml);
   // Merge known finite values only; malformed/partial chunks cannot destroy the parameter tree.
   auto safe=state.copyState();
   for(auto child:incoming) {
    auto id=child.getProperty("id").toString();
    if(auto* p=state.getParameter(id)) {
     if(!child.hasProperty("value")) continue;
     const auto value=static_cast<float>(child.getProperty("value"));
     if(!std::isfinite(value)) continue;
     for(auto existing:safe) if(existing.getProperty("id").toString()==id)
      existing.setProperty("value",p->convertFrom0to1(juce::jlimit(0.0f,1.0f,p->convertTo0to1(value))),nullptr);
    }
   }
   state.replaceState(safe);
  }
}
juce::AudioProcessorEditor* RecallProcessor::createEditor(){return new RecallEditor(*this);}
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter(){return new RecallProcessor();}
