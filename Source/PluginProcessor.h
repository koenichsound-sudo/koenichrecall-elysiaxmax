#pragma once
#include "Parameters.h"
class RecallProcessor final : public juce::AudioProcessor {
public:
 RecallProcessor();
 juce::AudioProcessorValueTreeState state;
 static juce::AudioProcessorValueTreeState::ParameterLayout makeParameters();
 const juce::String getName() const override { return "Koenich Recall - elysia xMax"; }
 void prepareToPlay(double,int) override {}
 void releaseResources() override {}
 bool isBusesLayoutSupported(const BusesLayout&) const override;
 void processBlock(juce::AudioBuffer<float>&,juce::MidiBuffer&) override {}
 void processBlock(juce::AudioBuffer<double>&,juce::MidiBuffer&) override {}
 bool supportsDoublePrecisionProcessing() const override {return true;}
 bool hasEditor() const override {return true;}
 juce::AudioProcessorEditor* createEditor() override;
 bool acceptsMidi() const override {return false;}
 bool producesMidi() const override {return false;}
 double getTailLengthSeconds() const override {return 0;}
 int getNumPrograms() override {return 1;}
 int getCurrentProgram() override {return 0;}
 void setCurrentProgram(int) override {}
 const juce::String getProgramName(int) override {return {};}
 void changeProgramName(int,const juce::String&) override {}
 void getStateInformation(juce::MemoryBlock&) override;
 void setStateInformation(const void*,int) override;
private:
 JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RecallProcessor)
};
