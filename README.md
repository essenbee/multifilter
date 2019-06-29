# multifilter
A VST plugin for different types of digital audio filter.

#### Episode 43

Created the default project and began adding the initial GUI elements to the plugin. Wired up the rotary sliders to `AudioParameters` okay, but struggled with hooking up the combobox to `AudioParameterChoice`.

It turns out that the solution to the issue we had was to wire up the combobox to an `AudioParameterInt` parameter instead, like this:
```
    auto filterTypeParam = std::make_unique<AudioParameterInt>("filter_type", "Filter_Type", 1, 29, 1);
```
and to populate the combobox in the `PluginEditor.cpp` file like this:
```
    	filterTypeControl.addItemList(
		{ "LPF1P", "LPF1", "HPF1", "LPF2", "HPF2", "BPF2", "BSF2", "ButterLPF2", "ButterHPF2",
		  "ButterBPF2", "ButterSF2", "MMALPF2", "MMALPF2B", "LowShelf", "HighShelf", "NCQParaEQ",
		  "CQParaEQ", "LWRLPF2", "LWRHPF2", "APF1", "APF2", "ResonA", "ResonB", "MatchLP2A",
		  "MatchLP2B", "MatchBP2A", "MatchBF2B", "ImpInvLP1", "ImpInvLP2" }, 1);
```
This associates the parameter value 1 with the first option in the combobox (`LPF1P` in this case), and so forth.

#### Episode 44

TBC
