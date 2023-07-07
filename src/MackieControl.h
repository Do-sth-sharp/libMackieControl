/*****************************************************************//**
 * \file	MackieControl.h
 * \brief	A compact Mackie Control library on JUCE.
 * 
 * \author	WuChang
 * \email	31423836@qq.com
 * \date	July 2023
 * \version	1.0.0
 * \license	MIT License
 *********************************************************************/

#pragma once

#include <JuceHeader.h>

namespace mackieControl {
	/**
	 * Mackie Control messages via MIDI system exclusive message.
	 */
	enum class SysExMessage : uint8_t {
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
	/**
	 * Valid Mackie Control messages via MIDI system exclusive message.
	 */
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
	/**
	 * Check if the message is valid.
	 */
	constexpr bool isValidSysExMessage(SysExMessage mes) { 
		return std::find(validSysExMessage.begin(), validSysExMessage.end(), mes) != validSysExMessage.end(); }
	/**
	 * Check if the message is valid.
	 */
	constexpr bool isValidSysExMessage(int mes) {
		return isValidSysExMessage(static_cast<SysExMessage>(mes)); }

	/**
	 * Mackie Control messages via MIDI note message velocity data.
	 */
	enum class VelocityMessage : uint8_t {
		Off = 0,
		Flashing,
		On = 127
	};
	/**
	 * Valid Mackie Control messages via MIDI note message velocity data.
	 */
	constinit auto validVelocityMessage = std::to_array({
		VelocityMessage::Off,
		VelocityMessage::Flashing,
		VelocityMessage::On
		});
	/**
	 * Check if the message is valid.
	 */
	constexpr bool isValidVelocityMessage(VelocityMessage mes) {
		return std::find(validVelocityMessage.begin(), validVelocityMessage.end(), mes) != validVelocityMessage.end(); }
	/**
	 * Check if the message is valid.
	 */
	constexpr bool isValidVelocityMessage(int mes) {
		return isValidVelocityMessage(static_cast<VelocityMessage>(mes)); }

	/**
	 * Mackie Control messages via MIDI note message note number data.
	 */
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
	/**
	 * Valid Mackie Control messages via MIDI note message note number data.
	 */
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
	/**
	 * Check if the message is valid.
	 */
	constexpr bool isValidNoteMessage(NoteMessage mes) {
		return std::find(validNoteMessage.begin(), validNoteMessage.end(), mes) != validNoteMessage.end(); }
	/**
	 * Check if the message is valid.
	 */
	constexpr bool isValidNoteMessage(int mes) {
		return isValidNoteMessage(static_cast<NoteMessage>(mes)); }

	/**
	 * Mackie Control messages via MIDI controller message controller number data.
	 */
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
	/**
	 * Valid Mackie Control messages via MIDI controller message controller number data.
	 */
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
	/**
	 * Check if the message is valid.
	 */
	constexpr bool isValidCCMessage(CCMessage mes) {
		return std::find(validCCMessage.begin(), validCCMessage.end(), mes) != validCCMessage.end(); }
	/**
	 * Check if the message is valid.
	 */
	constexpr bool isValidCCMessage(int mes) {
		return isValidCCMessage(static_cast<CCMessage>(mes)); }

	/**
	 * Rotation direction of wheel messages.
	 */
	enum class WheelType {
		CW, CCW
	};

	/**
	 * LED ring mode of V-Pot on Mackie Control devices.
	 */
	enum class VPotLEDRingMode {
		SingleDotMode,
		BoostCutMode,
		WrapMode,
		SpreadMode
	};

	/**
	 * Mackie Control Message class.
	 */
	class Message final {
	public:
		/**
		 * Create an empty Mackie Control message. An empty message is an invalid Mackie Control message.
		 */
		Message() = default;
		/**
		 * Create a Mackie Control message from a MIDI message.
		 */
		explicit Message(const juce::MidiMessage& midiMessage);

		/**
		 * Create a copy of another message.
		 */
		explicit Message(const Message& message);
		/**
		 * Move constructor.
		 */
		explicit Message(Message&& message) noexcept;

		/**
		 * Copy this message from another one.
		 */
		Message& operator=(const Message& message);
		/**
		 * Move assignment operator.
		 */
		Message& operator=(Message&& message) noexcept;

		/**
		 * Copy this message from a MIDI message.
		 */
		Message& operator=(const juce::MidiMessage& message);
		/**
		 * Convert this message to MIDI message.
		 */
		juce::MidiMessage toMidi() const;

		/**
		 * Check if this message is a valid Mackie Control message via MIDI system exclusive message.
		 */
		bool isSysEx() const;
		/**
		 * Check if this message is a valid Mackie Control message via MIDI note message.
		 */
		bool isNote() const;
		/**
		 * Check if this message is a valid Mackie Control message via MIDI controller message.
		 */
		bool isCC() const;
		/**
		 * Check if this message is a valid Mackie Control message via MIDI pitch wheel message.
		 */
		bool isPitchWheel() const;
		/**
		 * Check if this message is a valid Mackie Control message via MIDI channel pressure message.
		 */
		bool isChannelPressure() const;

		/**
		 * Check if this message is a valid Mackie Control message.
		 */
		bool isMackieControl() const;

		/**
		 * Get the type of Mackie Control message via MIDI system exclusive message.
		 * \return	Message Type
		 */
		std::tuple<SysExMessage> getSysExData() const;
		/**
		 * Get the Host Connection Query message data.
		 * \return	Serial Number, Challenge Code
		 */
		std::tuple<std::array<uint8_t, 7>, uint32_t> getHostConnectionQueryData() const;
		/**
		 * Get the Host Connection Reply message data.
		 * \return	Serial Number, Response Code
		 */
		std::tuple<std::array<uint8_t, 7>, uint32_t> getHostConnectionReplyData() const;
		/**
		 * Get the Host Connection Confirmation message data.
		 * \return	Serial Number
		 */
		std::tuple<std::array<uint8_t, 7>> getHostConnectionConfirmationData() const;
		/**
		 * Get the Host Connection Error message data.
		 * \return	Serial Number
		 */
		std::tuple<std::array<uint8_t, 7>> getHostConnectionErrorData() const;
		/**
		 * Get the LCD Back Light Saver message data.
		 * \return	Back Light On/Off, Timeout
		 */
		std::tuple<uint8_t, uint8_t> getLCDBackLightSaverData() const;
		/**
		 * Get the Touchless Movable Faders message data.
		 * \return	Touch On/Off
		 */
		std::tuple<uint8_t> getTouchlessMovableFadersData() const;
		/**
		 * Get the Fader Touch Sensitivity message data.
		 * \return	 Channel Number, Value
		 */
		std::tuple<uint8_t, uint8_t> getFaderTouchSensitivityData() const;
		/**
		 * Get the Time Code/BBT Display message data.
		 * \return	Data Pointer, Data Size
		 */
		std::tuple<const uint8_t*, int> getTimeCodeBBTDisplayData() const;
		/**
		 * Get the Assignment 7-Segment Display message data.
		 * \return	Data
		 */
		std::tuple<std::array<uint8_t, 2>> getAssignment7SegmentDisplayData() const;
		/**
		 * Get the LCD message data.
		 * \return	Line Place, Data Pointer, Data Size
		 */
		std::tuple<uint8_t, const char*, int> getLCDData() const;
		/**
		 * Get the Version Reply message data.
		 * \return	Value Pointer, Value Size
		 */
		std::tuple<const char*, int> getVersionReplyData() const;
		/**
		 * Get the Channel Meter Mode message data.
		 * \return	Channel Number, Mode
		 */
		std::tuple<uint8_t, uint8_t> getChannelMeterModeData() const;
		/**
		 * Get the Global LCD Meter Mode message data.
		 * \return	Horizontal/Vertical Mode
		 */
		std::tuple<uint8_t> getGlobalLCDMeterModeData() const;
		/**
		 * Get the type of Mackie Control message via MIDI note message.
		 * \return	Message Type, Message On/Off Type
		 */
		std::tuple<NoteMessage, VelocityMessage> getNoteData() const;
		/**
		 * Get the type of Mackie Control message via MIDI controller message.
		 * \return	Message Type, Value
		 */
		std::tuple<CCMessage, int> getCCData() const;
		/**
		 * Get the type of Mackie Control message via MIDI pitch wheel message.
		 * \return	Channel Number, Fader Value
		 */
		std::tuple<int, int> getPitchWheelData() const;
		/**
		 * Get the type of Mackie Control message via MIDI channel pressure message.
		 * \return	Meter Channel Number, Meter Value
		 */
		std::tuple<int, int> getChannelPressureData() const;

	public:
		/**
		 * Convert MIDI message to Mackie Control message.
		 */
		static Message fromMidi(const juce::MidiMessage& message);
		/**
		 * Convert Mackie Control message to MIDI message.
		 */
		static juce::MidiMessage toMidi(const Message& message);

		/**
		 * Create a Device Query message.
		 */
		static Message createDeviceQuery();
		/**
		 * Create a Host Connection Query message.
		 * \param serialNum		Serial Number
		 * \param challengeCode	Challenge Code
		 */
		static Message createHostConnectionQuery(const std::array<uint8_t, 7>& serialNum, uint32_t challengeCode);
		/**
		 * Create a Host Connection Reply message.
		 * \param serialNum		Serial Number
		 * \param responseCode	Response Code
		 */
		static Message createHostConnectionReply(const std::array<uint8_t, 7>& serialNum, uint32_t responseCode);
		/**
		 * Create a Host Connection Confirmation message.
		 * \param serialNum		Serial Number
		 */
		static Message createHostConnectionConfirmation(const std::array<uint8_t, 7>& serialNum);
		/**
		 * Create a Host Connection Error message.
		 * \param serialNum		Serial Number
		 */
		static Message createHostConnectionError(const std::array<uint8_t, 7>& serialNum);
		/**
		 * Create an LCD Back Light Saver message.
		 * \param state			Back Light On/Off
		 * \param timeout		Timeout (min)
		 */
		static Message createLCDBackLightSaver(uint8_t state, uint8_t timeout);
		/**
		 * Create a Touchless Movable Faders message.
		 * \param state			Touch On/Off
		 */
		static Message createTouchlessMovableFaders(uint8_t state);
		/**
		 * Create a Fader Touch Sensitivity message.
		 * \param channelNumber	Channel Number
		 * \param value			Value
		 */
		static Message createFaderTouchSensitivity(uint8_t channelNumber, uint8_t value);
		/**
		 * Create a Go Offline message.
		 */
		static Message createGoOffline();
		/**
		 * Create a Time Code/BBT Display message. This will create the own copy of the data.
		 * \param data			Data Pointer (Mackie Control Character)
		 * \param size			Data Size
		 */
		static Message createTimeCodeBBTDisplay(const uint8_t* data, int size);
		/**
		 * Create an Assignment 7-Segment Display message.
		 * \param data			Data (Mackie Control Character)
		 */
		static Message createAssignment7SegmentDisplay(const std::array<uint8_t, 2>& data);
		/**
		 * Create an LCD message. This will create the own copy of the data.
		 * \param place			Line Place
		 * \param data			Data Pointer
		 * \param size			Data Size
		 */
		static Message createLCD(uint8_t place, const char* data, int size);
		/**
		 * Create a Version Request message.
		 */
		static Message createVersionRequest();
		/**
		 * Create a Version Reply message. This will create the own copy of the data.
		 * \param data			Data Pointer
		 * \param size			Data Size
		 */
		static Message createVersionReply(const char* data, int size);
		/**
		 * Create a Channel Meter Mode message.
		 * \param channelNumber	Channel Number
		 * \param mode			Mode
		 */
		static Message createChannelMeterMode(uint8_t channelNumber, uint8_t mode);
		/**
		 * Create a Global LCD Meter Mode message.
		 * \param mode			Horizontal/Vertical Mode
		 */
		static Message createGlobalLCDMeterMode(uint8_t mode);
		/**
		 * Create an All Faders to Minimum message.
		 */
		static Message createAllFaderstoMinimum();
		/**
		 * Create an All LEDs Off message.
		 */
		static Message createAllLEDsOff();
		/**
		 * Create a Reset message.
		 */
		static Message createReset();
		/**
		 * Create a Mackie Control message via MIDI note message.
		 * \param type			Message Type
		 * \param vel			Message On/Off Type
		 */
		static Message createNote(NoteMessage type, VelocityMessage vel);
		/**
		 * Create a Mackie Control message via MIDI controller message.
		 * \param type			Message Type
		 * \param value			Value
		 */
		static Message createCC(CCMessage type, int value);
		/**
		 * Create a Mackie Control message via MIDI pitch wheel message.
		 * \param channel		Channel Number
		 * \param value			Fader Value
		 */
		static Message createPitchWheel(int channel, int value);
		/**
		 * Create a Mackie Control message via MIDI channel pressure message.
		 * \param channel		Meter Channel Number
		 * \param value			Meter Value
		 */
		static Message createChannelPressure(int channel, int value);

		/**
		 * Convert ASCII character to Mackie Control character.
		 */
		static uint8_t charToMackie(char c);
		/**
		 * Convert Mackie Control character to ASCII character.
		 */
		static char mackieToChar(uint8_t c);

		/**
		 * Create place param of LCD message.
		 * \param lowerLine		Upper/Lower Line
		 * \param index			Character Index
		 */
		static uint8_t toLCDPlace(bool lowerLine, uint8_t index);
		/**
		 * Create mode param of Channel Meter Mode message.
		 * \param signalLEDEnabled			Signal LED Enabled
		 * \param peakHoldDisplayEnabled	Peak Hold Display Enabled
		 * \param LCDLevelMeterEnabled		LCD Level Meter Enabled
		 */
		static uint8_t toChannelMeterMode(
			bool signalLEDEnabled, bool peakHoldDisplayEnabled, bool LCDLevelMeterEnabled);
		/**
		 * Create value param of V-Pot message.
		 * \param type			Wheel Rotation Direction
		 * \param ticks			Wheel Rotation Ticks
		 */
		static int toVPotValue(WheelType type, int ticks);
		/**
		 * Create value param of V-Pot LED Ring message.
		 * \param centerLEDOn	Center LED On/Off
		 * \param mode			LED Ring Mode
		 * \param value			Value
		 */
		static int toVPotLEDRingValue(bool centerLEDOn, VPotLEDRingMode mode, int value);
		/**
		 * Create value param of Jog Wheel message.
		 * \param type			Wheel Rotation Direction
		 * \param ticks			Wheel Rotation Ticks
		 */
		static int toJogWheelValue(WheelType type, int ticks);

		/**
		 * Get place data of LCD message.
		 * \return	Upper/Lower Line, Character Index
		 */
		static std::tuple<bool, uint8_t> convertLCDPlace(uint8_t place);
		/**
		 * Get mode data of Channel Meter Mode message.
		 * \return	Signal LED Enabled, Peak Hold Display Enabled, LCD Level Meter Enabled
		 */
		static std::tuple<bool, bool, bool> convertChannelMeterMode(uint8_t mode);
		/**
		 * Get value data of V-Pot message.
		 * \return	Wheel Rotation Direction, Wheel Rotation Ticks
		 */
		static std::tuple<WheelType, int> convertVPotValue(int value);
		/**
		 * Get value data of V-Pot LED Ring message.
		 * \return	Center LED On/Off, LED Ring Mode, Value
		 */
		static std::tuple<bool, VPotLEDRingMode, int> convertVPotLEDRingValue(int value);
		/**
		 * Get value data of Jog Wheel message.
		 * \return	Wheel Rotation Direction, Wheel Rotation Ticks
		 */
		static std::tuple<WheelType, int> convertJogWheelValue(int value);

	private:
		juce::MidiMessage message;

		JUCE_LEAK_DETECTOR(Message);
	};
}
