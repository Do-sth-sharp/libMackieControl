# Mackie Control
## What Is Mackie Control
Mackie Control is a device control protocol designed by Mackie based on the MIDI protocol. This protocol utilizes MIDI system-exclusive events, note on/off events, CC events, pitch wheel events, and channel pressure events to transmit control information.  
**There are slight differences in the implementation of Mackie Control between different DAWs, and the protocol in this document is similar to that used by Logic.**  

## Mackie Control by System-Exclusive Events
|Value of sysExData[4]|Mackie Control Function|Other Bytes of sysExData|Comments|
|:-----|:-----|:-----|:-----|
|0|Device Query|-||
|1|Host Connection Query|[5:11] Serial Number <br> [12:15] Challenge Code||
|2|Host Connection Reply|[5:11] Serial Number <br> [12:15] Response Code||
|3|Host Connection Confirmation|[5:11] Serial Number||
|4|Host Connection Error|[5:11] Serial Number||
|11|LCD Back Light Saver|[5] {0}: Off {Other}: On <br> [6] Timeout (min)|Timeout exists only when backlight is on|
|12|Touchless Movable Faders|[5] {0}: Touch On {Other}: Touch Off||
|14|Fader Touch Sensitivity|[5] Channel Number <br> [6] Value||
|15|Go Offline|-||
|16|Time Code/BBT Display|[6:(size-2)] Data|Mackie Char, From right to left|
|17|Assignment 7-Segment Display|[6:7] Data|Mackie Char, From right to left|
|18|LCD|[5] {0:55}: Upper Line {56:111}: Lower Line <br> [6:(size-1)] Data|The data is in ASCII format|
|19|Version Request|-||
|20|Version Reply|[6:(size-1)] Value|The value is in ASCII format|
|32|Channel Meter Mode|[5] Channel Number <br> [6] Mode|Mode BitMask: <br> {1}: Signal LED Enabled <br> {2}: Peak Hold Display Enabled <br> {4}: LCD Level Meter Enabled|
|33|Global LCD Meter Mode|[5] {0}: Horizontal {Other}: Vertical||
|97|All Faders to Minimum|-||
|98|All LEDs Off|-||
|99|Reset|-||

## Mackie Control by Note On/Off Events
|Note Velocity|Mackie Control Function|
|:-----|:-----|
|0|Off|
|1|Flashing|
|127|On|

|Note Number|Mackie Control Function|Comments|
|:-----|:-----|:-----|
|0:7|REC/RDY Ch.|Accept velocity data <br> Channel Number = Note Number % 8 + 1|
|8:15|SOLO Ch.|Accept velocity data <br> Channel Number = Note Number % 8 + 1|
|16:23|MUTE Ch.|Accept velocity data <br> Channel Number = Note Number % 8 + 1|
|24:31|SELECT Ch.|Accept velocity data <br> Channel Number = Note Number % 8 + 1|
|32:39|V-Select Ch.|Accept velocity data <br> Channel Number = Note Number % 8 + 1|
|40|ASSIGNMENT: TRACK||
|41|ASSIGNMENT: SEND||
|42|ASSIGNMENT: PAN/SURROUND||
|43|ASSIGNMENT: PLUG-IN||
|44|ASSIGNMENT: EQ||
|45|ASSIGNMENT: INSTRUMENT||
|46|FADER BANKS: BANK Left|Accept velocity data|
|47|FADER BANKS: BANK Right|Accept velocity data|
|48|FADER BANKS: CHANNEL Left|Accept velocity data|
|49|FADER BANKS: CHANNEL Right|Accept velocity data|
|50|FLIP|Accept velocity data|
|51|GLOBAL VIEW|Accept velocity data|
|52|NAME/VALUE||
|53|SMPTE/BEATS||
|54:61|Function|Function Number = Note Number - 53|
|62|GLOBAL VIEW: MIDI TRACKS||
|63|GLOBAL VIEW: INPUTS||
|64|GLOBAL VIEW: AUDIO TRACKS||
|65|GLOBAL VIEW: AUDIO INSTRUMENT||
|66|GLOBAL VIEW: AUX||
|67|GLOBAL VIEW: BUSSES||
|68|GLOBAL VIEW: OUTPUTS||
|69|GLOBAL VIEW: USER||
|70|SHIFT|Accept velocity data|
|71|OPTION|Accept velocity data|
|72|CONTROL|Accept velocity data|
|73|CMD/ALT|Accept velocity data|
|74|AUTOMATION: READ/OFF||
|75|AUTOMATION: WRITE||
|76|AUTOMATION: TRIM||
|77|AUTOMATION: TOUCH||
|78|AUTOMATION: LATCH||
|79|GROUP||
|80|UTILITIES: SAVE||
|81|UTILITIES: UNDO||
|82|UTILITIES: CANCEL||
|83|UTILITIES: ENTER||
|84|MARKER||
|85|NUDGE||
|86|CYCLE||
|87|DROP||
|88|REPLACE||
|89|CLICK||
|90|SOLO||
|91|REWIND|Accept velocity data|
|92|FAST FWD|Accept velocity data|
|93|STOP|Accept velocity data|
|94|PLAY|Accept velocity data|
|95|RECORD|Accept velocity data|
|96|Cursor Up|Accept velocity data|
|97|Cursor Down|Accept velocity data|
|98|Cursor Left|Accept velocity data|
|99|Cursor Right|Accept velocity data|
|100|Zoom|Accept velocity data|
|101|Scrub|Accept velocity data|
|102|User Switch A||
|103|User Switch B||
|104:111|Fader Touch Ch.|Accept velocity data <br> Channel Number = Note Number - 103|
|112|Fader Touch Master||
|113|SMPTE LED||
|114|BEATS LED||
|115|RUDE SOLO LIGHT||
|116|Relay click||

## Mackie Control by CC Events
|CC Channel|Mackie Control Function|CC Value|Comments|
|:-----|:-----|:-----|:-----|
|16:23|V-Pot|{0:62}: CW {Other}: CCW|Channel Number = CC Channel Number - 15 <br> Ticks = CC Value % 64|
|46|External Controller|Controller Value||
|48:55|V-Pot LED Ring|{0:63}: Center LED Off {Other}: Center LED On|Channel Number = CC Channel Number - 47 <br> CC Value % 64 between 0 and 15: Single Dot Mode <br> CC Value % 64 between 16 and 31: Boost/Cut Mode <br> CC Value % 64 between 32 and 47: Wrap Mode <br> CC Value % 64 between 48 and 63: Spread Mode <br> Value = CC Value % 16|
|60|Jog Wheel|{0:62}: CW {Other}: CCW|Ticks = CC Value % 64|
|64:73|Time Code/BBT Display|Mackie Character|Digit = 74 - CC Channel Number|
|74:76|Assignment 7-Segment Display|Mackie Character|CC Channel Number: <br> {74}: Right <br> {Other}: Left|

## Mackie Control by Pitch Wheel Events
Mackie Control utilizes MIDI pitch wheel events to control faders.  
When MIDI channel number is 1:8, the fader channel is 1-8; when MIDI channel number is 9, the fader channel is the master channel.  
The pitch wheel value is the fader value.  

## Mackie Control by Channel Pressure Events
Mackie Control utilizes MIDI channel pressure events to control meter values.  
Meter Channel Number = Channel Pressure Value / 16 + 1.  
When Channel Pressure Value % 16 between 0 and 12, Meter Value = (Channel Pressure Value % 16) / 12 * 100%.  
When Channel Pressure Value % 16 is 14, set meter channel overload.  
When Channel Pressure Value % 16 is 15, clear meter channel overload.  

## Mackie Character Format
You can convert ASCII char to Mackie char by this:
```cpp
uint8_t charToMackie(char c) {
	if (c >= 'a' && c <= 'z') { return static_cast<uint8_t>((c - 'a') + 1); }
	else if (c >= 'A' && c <= 'Z') { return static_cast<uint8_t>((c - 'A') + 1); }
	else if (c >= '0' && c <= '9') { return static_cast<uint8_t>((c - '0') + 0x30); }

	return 0x20;
}
```

## References
[mackie-control-monitor](https://github.com/tony-had/mackie-control-monitor)  
[V2Mackie](https://github.com/versioduo/V2Mackie)  
[tracktion_engine](https://github.com/Tracktion/tracktion_engine)  
[mc_protocol_mappings](http://www.midibox.org/dokuwiki/doku.php?id=mc_protocol_mappings)  
[Mackie Control MIDI Map](http://www.jjlee.com/qlab/Mackie%20Control%20MIDI%20Map.pdf)  
