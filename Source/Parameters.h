#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <array>
namespace recall {
struct Spec { const char* id; const char* name; float min, max, step, initial; const char* unit; float x,y; bool logarithmic; };
inline constexpr std::array<Spec,12> specs {{
 {"link","Link",0,100,0.1f,0," %",146,128,false},
 {"tone","Tone",-8,8,0.1f,0,"",495,128,false},
 {"mid_thres","Mid Thres",0,100,0.1f,0," %",146,320,false},
 {"mid_gain","Mid Gain",-12,12,0.1f,0," dB",495,320,false},
 {"side_thres","Side Thres",0,100,0.1f,0," %",146,512,false},
 {"side_gain","Side Gain",-12,12,0.1f,0," dB",495,512,false},
 {"low_thres","Low Thres",0,100,0.1f,0," %",146,704,false},
 {"low_gain","Low Gain",-12,12,0.1f,0," dB",495,704,false},
 {"x_freq","X-Freq",40,470,1,140," Hz",146,897,true},
 {"s_clip","S-Clip",0,100,0.1f,0," %",495,897,false},
 {"time","Time",10,1300,1,180," ms",146,1089,true},
 {"level","Level",-12,12,0.1f,0," dB",495,1089,false}
}};
inline constexpr std::array<const char*,3> toggleIDs {"lowmo","punch","hit_it"};
inline constexpr std::array<const char*,3> toggleNames {"LOWMO","PUNCH","HIT IT!"};
inline juce::NormalisableRange<float> range(const Spec& s) {
 // Time's printed hardware scale is not a single logarithmic curve.
 // Interpolate logarithmically between measured angular scale anchors.
 if (juce::String(s.id) == "time") {
  const std::array<float,6> values {10,20,180,400,900,1300};
  const std::array<float,6> positions {0,0.18f,0.5f,0.6433333f,0.82f,1};
  return {s.min,s.max,
   [values,positions](float,float,float p) {
    p=juce::jlimit(0.0f,1.0f,p);
    for(size_t i=1;i<positions.size();++i) if(p<=positions[i]) {
     const auto t=(p-positions[i-1])/(positions[i]-positions[i-1]);
     return values[i-1]*std::pow(values[i]/values[i-1],t);
    }
    return values.back();
   },
   [values,positions](float,float,float v) {
    v=juce::jlimit(values.front(),values.back(),v);
    for(size_t i=1;i<values.size();++i) if(v<=values[i]) {
     const auto t=std::log(v/values[i-1])/std::log(values[i]/values[i-1]);
     return positions[i-1]+t*(positions[i]-positions[i-1]);
    }
    return 1.0f;
   },
   [](float a,float b,float v){return juce::jlimit(a,b,std::round(v));}};
 }
 if (!s.logarithmic) return {s.min,s.max,s.step};
 juce::NormalisableRange<float> r(s.min,s.max,
  [](float a,float b,float p){return a*std::pow(b/a,p);},
  [](float a,float b,float v){return std::log(v/a)/std::log(b/a);},
  [](float a,float b,float v){return juce::jlimit(a,b,std::round(v));});
 return r;
}
}
