#pragma once

#include <JuceHeader.h>

namespace mackieControl {
	enum class SysExMessage {
		DeviceQuery = 0,
		HostConnectionQuery,
		HostConnectionReply,
		HostConnectionConfirmation,
		HostConnectionError,
		LCDBackLightSaver = 11,
		TouchlessMovableFaders,
		FaderTouchSensitivity = 14,
		GoOffline,
		TimeCodeBBTDisplay,
		Assignment7SegmentDisplay,
		LCD,
		VersionRequest,
		VersionReply,
		ChannelMeterMode = 32,
		GlobalLCDMeterMode,
		AllFaderstoMinimum = 97,
		AllLEDsOff,
		Reset
	};
	constinit auto validSysExMessage = std::to_array({
		SysExMessage::DeviceQuery,
		SysExMessage::HostConnectionQuery,
		SysExMessage::HostConnectionReply,
		SysExMessage::HostConnectionConfirmation,
		SysExMessage::HostConnectionError,
		SysExMessage::LCDBackLightSaver,
		SysExMessage::TouchlessMovableFaders,
		SysExMessage::FaderTouchSensitivity,
		SysExMessage::GoOffline,
		SysExMessage::TimeCodeBBTDisplay,
		SysExMessage::Assignment7SegmentDisplay,
		SysExMessage::LCD,
		SysExMessage::VersionRequest,
		SysExMessage::VersionReply,
		SysExMessage::ChannelMeterMode,
		SysExMessage::GlobalLCDMeterMode,
		SysExMessage::AllFaderstoMinimum,
		SysExMessage::AllLEDsOff,
		SysExMessage::Reset
		});
	constexpr bool isValidSysExMessage(SysExMessage mes) { 
		return std::find(validSysExMessage.begin(), validSysExMessage.end(), mes) != validSysExMessage.end(); }
	constexpr bool isValidSysExMessage(int mes) {
		return isValidSysExMessage(static_cast<SysExMessage>(mes)); }

	enum class VelocityMessage {
		Off = 0,
		Flashing,
		On = 127
	};
	constinit auto validVelocityMessage = std::to_array({
		VelocityMessage::Off,
		VelocityMessage::Flashing,
		VelocityMessage::On
		});
	constexpr bool isValidVelocityMessage(VelocityMessage mes) {
		return std::find(validVelocityMessage.begin(), validVelocityMessage.end(), mes) != validVelocityMessage.end(); }
	constexpr bool isValidVelocityMessage(int mes) {
		return isValidVelocityMessage(static_cast<VelocityMessage>(mes)); }

	enum class NoteMessage {
		RECRDYCh1, RECRDYCh2, RECRDYCh3, RECRDYCh4, RECRDYCh5, RECRDYCh6, RECRDYCh7, RECRDYCh8,
		SOLOCh1, SOLOCh2, SOLOCh3, SOLOCh4, SOLOCh5, SOLOCh6, SOLOCh7, SOLOCh8,
		MUTECh1, MUTECh2, MUTECh3, MUTECh4, MUTECh5, MUTECh6, MUTECh7, MUTECh8,
		SELECTCh1, SELECTCh2, SELECTCh3, SELECTCh4, SELECTCh5, SELECTCh6, SELECTCh7, SELECTCh8,
		VSelectCh1, VSelectCh2, VSelectCh3, VSelectCh4, VSelectCh5, VSelectCh6, VSelectCh7, VSelectCh8,
		ASSIGNMENTTRACK, ASSIGNMENTSEND, ASSIGNMENTPANSURROUND, ASSIGNMENTPLUGIN, ASSIGNMENTEQ, ASSIGNMENTINSTRUMENT,
		FADERBANKSBANKLeft, FADERBANKSBANKRight, FADERBANKSCHANNELLeft, FADERBANKSCHANNELRight,
		FLIP,
		GLOBALVIEW,
		NAMEVALUE,
		SMPTEBEATS,
		Function1, Function2, Function3, Function4, Function5, Function6, Function7, Function8,
		GLOBALVIEWMIDITRACKS, GLOBALVIEWINPUTS, GLOBALVIEWAUDIOTRACKS, GLOBALVIEWAUDIOINSTRUMENT,
		GLOBALVIEWAUX, GLOBALVIEWBUSSES, GLOBALVIEWOUTPUTS, GLOBALVIEWUSER,
		SHIFT, OPTION, CONTROL, CMDALT,
		AUTOMATIONREADOFF, AUTOMATIONWRITE, AUTOMATIONTRIM, AUTOMATIONTOUCH, AUTOMATIONLATCH,
		GROUP,
		UTILITIESSAVE, UTILITIESUNDO, UTILITIESCANCEL, UTILITIESENTER,
		MARKER,
		NUDGE,
		CYCLE,
		DROP,
		REPLACE,
		CLICK,
		SOLO,
		REWIND, FASTFWD, STOP, PLAY, RECORD,
		CursorUp, CursorDown, CursorLeft, CursorRight,
		Zoom,
		Scrub,
		UserSwitchA, UserSwitchB,
		FaderTouchCh1, FaderTouchCh2, FaderTouchCh3, FaderTouchCh4,
		FaderTouchCh5, FaderTouchCh6, FaderTouchCh7, FaderTouchCh8,
		FaderTouchMaster,
		SMPTELED,
		BEATSLED,
		RUDESOLOLIGHT,
		Relayclick
	};
	constinit auto validNoteMessage = std::to_array({
		NoteMessage::RECRDYCh1, NoteMessage::RECRDYCh2, NoteMessage::RECRDYCh3, NoteMessage::RECRDYCh4,
		NoteMessage::RECRDYCh5, NoteMessage::RECRDYCh6, NoteMessage::RECRDYCh7, NoteMessage::RECRDYCh8,
		NoteMessage::SOLOCh1, NoteMessage::SOLOCh2, NoteMessage::SOLOCh3, NoteMessage::SOLOCh4,
		NoteMessage::SOLOCh5, NoteMessage::SOLOCh6, NoteMessage::SOLOCh7, NoteMessage::SOLOCh8,
		NoteMessage::MUTECh1, NoteMessage::MUTECh2, NoteMessage::MUTECh3, NoteMessage::MUTECh4,
		NoteMessage::MUTECh5, NoteMessage::MUTECh6, NoteMessage::MUTECh7, NoteMessage::MUTECh8,
		NoteMessage::SELECTCh1, NoteMessage::SELECTCh2, NoteMessage::SELECTCh3, NoteMessage::SELECTCh4,
		NoteMessage::SELECTCh5, NoteMessage::SELECTCh6, NoteMessage::SELECTCh7, NoteMessage::SELECTCh8,
		NoteMessage::VSelectCh1, NoteMessage::VSelectCh2, NoteMessage::VSelectCh3, NoteMessage::VSelectCh4,
		NoteMessage::VSelectCh5, NoteMessage::VSelectCh6, NoteMessage::VSelectCh7, NoteMessage::VSelectCh8,
		NoteMessage::ASSIGNMENTTRACK, NoteMessage::ASSIGNMENTSEND, NoteMessage::ASSIGNMENTPANSURROUND,
		NoteMessage::ASSIGNMENTPLUGIN, NoteMessage::ASSIGNMENTEQ, NoteMessage::ASSIGNMENTINSTRUMENT,
		NoteMessage::FADERBANKSBANKLeft, NoteMessage::FADERBANKSBANKRight,
		NoteMessage::FADERBANKSCHANNELLeft, NoteMessage::FADERBANKSCHANNELRight,
		NoteMessage::FLIP,
		NoteMessage::GLOBALVIEW,
		NoteMessage::NAMEVALUE,
		NoteMessage::SMPTEBEATS,
		NoteMessage::Function1, NoteMessage::Function2, NoteMessage::Function3, NoteMessage::Function4,
		NoteMessage::Function5, NoteMessage::Function6, NoteMessage::Function7, NoteMessage::Function8,
		NoteMessage::GLOBALVIEWMIDITRACKS, NoteMessage::GLOBALVIEWINPUTS,
		NoteMessage::GLOBALVIEWAUDIOTRACKS, NoteMessage::GLOBALVIEWAUDIOINSTRUMENT,
		NoteMessage::GLOBALVIEWAUX, NoteMessage::GLOBALVIEWBUSSES,
		NoteMessage::GLOBALVIEWOUTPUTS, NoteMessage::GLOBALVIEWUSER,
		NoteMessage::SHIFT, NoteMessage::OPTION, NoteMessage::CONTROL, NoteMessage::CMDALT,
		NoteMessage::AUTOMATIONREADOFF, NoteMessage::AUTOMATIONWRITE, NoteMessage::AUTOMATIONTRIM,
		NoteMessage::AUTOMATIONTOUCH, NoteMessage::AUTOMATIONLATCH,
		NoteMessage::GROUP,
		NoteMessage::UTILITIESSAVE, NoteMessage::UTILITIESUNDO,
		NoteMessage::UTILITIESCANCEL, NoteMessage::UTILITIESENTER,
		NoteMessage::MARKER,
		NoteMessage::NUDGE,
		NoteMessage::CYCLE,
		NoteMessage::DROP,
		NoteMessage::REPLACE,
		NoteMessage::CLICK,
		NoteMessage::SOLO,
		NoteMessage::REWIND, NoteMessage::FASTFWD, NoteMessage::STOP, NoteMessage::PLAY, NoteMessage::RECORD,
		NoteMessage::CursorUp, NoteMessage::CursorDown, NoteMessage::CursorLeft, NoteMessage::CursorRight,
		NoteMessage::Zoom,
		NoteMessage::Scrub,
		NoteMessage::UserSwitchA, NoteMessage::UserSwitchB,
		NoteMessage::FaderTouchCh1, NoteMessage::FaderTouchCh2,
		NoteMessage::FaderTouchCh3, NoteMessage::FaderTouchCh4,
		NoteMessage::FaderTouchCh5, NoteMessage::FaderTouchCh6,
		NoteMessage::FaderTouchCh7, NoteMessage::FaderTouchCh8,
		NoteMessage::FaderTouchMaster,
		NoteMessage::SMPTELED,
		NoteMessage::BEATSLED,
		NoteMessage::RUDESOLOLIGHT,
		NoteMessage::Relayclick
		});
	constexpr bool isValidNoteMessage(NoteMessage mes) {
		return std::find(validNoteMessage.begin(), validNoteMessage.end(), mes) != validNoteMessage.end(); }
	constexpr bool isValidNoteMessage(int mes) {
		return isValidNoteMessage(static_cast<NoteMessage>(mes)); }

	enum class CCMessage {
		VPot1 = 16, VPot2, VPot3, VPot4, VPot5, VPot6, VPot7, VPot8,
		ExternalController = 46,
		VPotLEDRing1 = 48, VPotLEDRing2, VPotLEDRing3, VPotLEDRing4,
		VPotLEDRing5, VPotLEDRing6, VPotLEDRing7, VPotLEDRing8,
		JogWheel = 60,
		TimeCodeBBTDisplay1 = 64, TimeCodeBBTDisplay2, TimeCodeBBTDisplay3, TimeCodeBBTDisplay4,
		TimeCodeBBTDisplay5, TimeCodeBBTDisplay6, TimeCodeBBTDisplay7, TimeCodeBBTDisplay8,
		TimeCodeBBTDisplay9, TimeCodeBBTDisplay10,
		Assignment7SegmentDisplay1, Assignment7SegmentDisplay2, Assignment7SegmentDisplay3
	};
	constinit auto validCCMessage = std::to_array({
		CCMessage::VPot1, CCMessage::VPot2, CCMessage::VPot3, CCMessage::VPot4,
		CCMessage::VPot5, CCMessage::VPot6, CCMessage::VPot7, CCMessage::VPot8,
		CCMessage::ExternalController,
		CCMessage::VPotLEDRing1, CCMessage::VPotLEDRing2, CCMessage::VPotLEDRing3, CCMessage::VPotLEDRing4,
		CCMessage::VPotLEDRing5, CCMessage::VPotLEDRing6, CCMessage::VPotLEDRing7, CCMessage::VPotLEDRing8,
		CCMessage::JogWheel,
		CCMessage::TimeCodeBBTDisplay1, CCMessage::TimeCodeBBTDisplay2,
		CCMessage::TimeCodeBBTDisplay3, CCMessage::TimeCodeBBTDisplay4,
		CCMessage::TimeCodeBBTDisplay5, CCMessage::TimeCodeBBTDisplay6,
		CCMessage::TimeCodeBBTDisplay7, CCMessage::TimeCodeBBTDisplay8,
		CCMessage::TimeCodeBBTDisplay9, CCMessage::TimeCodeBBTDisplay10,
		CCMessage::Assignment7SegmentDisplay1, CCMessage::Assignment7SegmentDisplay2,
		CCMessage::Assignment7SegmentDisplay3
		});
	constexpr bool isValidCCMessage(CCMessage mes) {
		return std::find(validCCMessage.begin(), validCCMessage.end(), mes) != validCCMessage.end(); }
	constexpr bool isValidCCMessage(int mes) {
		return isValidCCMessage(static_cast<CCMessage>(mes)); }

	enum class WheelType {
		CW, CCW
	};

	enum class VPotLEDRingMode {
		SingleDotMode,
		BoostCutMode,
		WrapMode,
		SpreadMode
	};

	class Message final {
	public:
		Message() = default;
		explicit Message(const juce::MidiMessage& midiMessage);

		explicit Message(const Message& message);
		explicit Message(Message&& message) noexcept;

		Message& operator=(const Message& message);
		Message& operator=(Message&& message) noexcept;

		Message& operator=(const juce::MidiMessage& message);
		juce::MidiMessage toMidi() const;

		bool isSysEx() const;
		bool isNote() const;
		bool isCC() const;
		bool isPitchWheel() const;
		bool isChannelPressure() const;

		bool isMackieControl() const;

	public:
		static Message fromMidi(const juce::MidiMessage& message);
		static juce::MidiMessage toMidi(const Message& message);

		/** TODO createSysEx */
		static Message createNote(NoteMessage type, VelocityMessage vel);
		static Message createCC(CCMessage type, int value);
		static Message createPitchWheel(int channel, int value);
		static Message createChannelPressure(int channel, int value);

	private:
		juce::MidiMessage message;

		JUCE_LEAK_DETECTOR(Message);
	};
}
