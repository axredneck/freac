 /* BonkEnc Audio Encoder
  * Copyright (C) 2001-2005 Robert Kausch <robert.kausch@bonkenc.org>
  *
  * This program is free software; you can redistribute it and/or
  * modify it under the terms of the "GNU General Public License".
  *
  * THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
  * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
  * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE. */

#include <dialogs/genconfig/genconfig_cdrip.h>

configureGeneralSettingsLayerCDRip::configureGeneralSettingsLayerCDRip() : Layer("CDRip")
{
	Point	 pos;
	Size	 size;

	currentConfig = bonkEnc::currentConfig;

	cdparanoia	= currentConfig->cdrip_paranoia;
	jitter		= currentConfig->cdrip_jitter;
	swapchannels	= currentConfig->cdrip_swapchannels;
	locktray	= currentConfig->cdrip_locktray;
	ntscsi		= currentConfig->cdrip_ntscsi;
	autoRead	= currentConfig->cdrip_autoRead;
	autoEject	= currentConfig->cdrip_autoEject;

	pos.x	= 7;
	pos.y	= 11;
	size.cx	= 344;
	size.cy	= 43;

	group_drive	= new GroupBox(bonkEnc::i18n->TranslateString("Active CD-ROM drive"), pos, size);

	pos.x	= 17;
	pos.y	= 23;
	size.cx	= 324;
	size.cy	= 0;

	combo_drive	= new ComboBox(pos, size);

	for (Int j = 0; j < currentConfig->cdrip_numdrives; j++)
	{
		combo_drive->AddEntry(currentConfig->cdrip_drives.GetNthEntry(j));
	}

	combo_drive->SelectEntry(currentConfig->cdrip_activedrive);

	pos.x	= 7;
	pos.y	= 66;
	size.cx	= 344;
	size.cy	= 65;

	group_ripping	= new GroupBox(bonkEnc::i18n->TranslateString("Ripper settings"), pos, size);

	pos.x	+= 10;
	pos.y	+= 13;
	size.cx	= 157;
	size.cy	= 0;

	check_paranoia	= new CheckBox(bonkEnc::i18n->TranslateString("Activate cdparanoia mode:"), pos, size, &cdparanoia);
	check_paranoia->onClick.Connect(&configureGeneralSettingsLayerCDRip::SetParanoia, this);

	pos.x	+= 166;
	pos.y	-= 1;
	size.cx	= 158;
	size.cy	= 0;

	combo_paranoia_mode= new ComboBox(pos, size);
	combo_paranoia_mode->AddEntry(bonkEnc::i18n->TranslateString("Overlap only"));
	combo_paranoia_mode->AddEntry(bonkEnc::i18n->TranslateString("No verify"));
	combo_paranoia_mode->AddEntry(bonkEnc::i18n->TranslateString("No scratch repair"));
	combo_paranoia_mode->AddEntry(bonkEnc::i18n->TranslateString("Full cdparanoia mode"));
	combo_paranoia_mode->SelectEntry(currentConfig->cdrip_paranoia_mode);

	if (!cdparanoia) combo_paranoia_mode->Deactivate();

	pos.x	-= 166;
	pos.y	+= 26;
	size.cx	= 157;
	size.cy	= 0;

	check_jitter	= new CheckBox(bonkEnc::i18n->TranslateString("Activate jitter correction"), pos, size, &jitter);

	pos.x += 166;

	check_swapchannels	= new CheckBox(bonkEnc::i18n->TranslateString("Swap left/right channel"), pos, size, &swapchannels);

	pos.x	= 359;
	pos.y	= 11;
	size.cx	= 178;
	size.cy	= 120;

	group_cdoptions	= new GroupBox(bonkEnc::i18n->TranslateString("CD options"), pos, size);

	pos.x	+= 10;
	pos.y	+= 14;
	size.cx	= 157;
	size.cy	= 0;

	check_autoRead	= new CheckBox(bonkEnc::i18n->TranslateString("Read CD contents on insert"), pos, size, &autoRead);

	pos.y += 26;

	check_autoEject	= new CheckBox(bonkEnc::i18n->TranslateString("Eject disk after ripping"), pos, size, &autoEject);

	pos.y += 26;

	check_locktray	= new CheckBox(bonkEnc::i18n->TranslateString("Lock CD tray while ripping"), pos, size, &locktray);

	pos.y += 26;

	check_ntscsi	= new CheckBox(bonkEnc::i18n->TranslateString("Use native NT SCSI library"), pos, size, &ntscsi);

	OSVERSIONINFOA	 vInfo;

	vInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);

	GetVersionExA(&vInfo);

	if (vInfo.dwPlatformId != VER_PLATFORM_WIN32_NT) check_ntscsi->Deactivate();

	RegisterObject(group_drive);
	RegisterObject(combo_drive);
	RegisterObject(group_ripping);
	RegisterObject(check_paranoia);
	RegisterObject(combo_paranoia_mode);
	RegisterObject(check_jitter);
	RegisterObject(check_swapchannels);
	RegisterObject(group_cdoptions);
	RegisterObject(check_autoRead);
	RegisterObject(check_autoEject);
	RegisterObject(check_locktray);
	RegisterObject(check_ntscsi);
}

configureGeneralSettingsLayerCDRip::~configureGeneralSettingsLayerCDRip()
{
	DeleteObject(group_drive);
	DeleteObject(combo_drive);
	DeleteObject(group_ripping);
	DeleteObject(check_paranoia);
	DeleteObject(combo_paranoia_mode);
	DeleteObject(check_jitter);
	DeleteObject(check_swapchannels);
	DeleteObject(group_cdoptions);
	DeleteObject(check_autoRead);
	DeleteObject(check_autoEject);
	DeleteObject(check_locktray);
	DeleteObject(check_ntscsi);
}

Void configureGeneralSettingsLayerCDRip::SetParanoia()
{
	if (cdparanoia)	combo_paranoia_mode->Activate();
	else		combo_paranoia_mode->Deactivate();
}

Int configureGeneralSettingsLayerCDRip::GetActiveDrive()
{
	return combo_drive->GetSelectedEntry()->id;
}

Int configureGeneralSettingsLayerCDRip::GetCDParanoiaMode()
{
	if (!cdparanoia) return -1;

	return combo_paranoia_mode->GetSelectedEntry()->id;
}

Bool configureGeneralSettingsLayerCDRip::GetJitter()
{
	return jitter;
}

Bool configureGeneralSettingsLayerCDRip::GetSwapChannels()
{
	return swapchannels;
}

Bool configureGeneralSettingsLayerCDRip::GetLockTray()
{
	return locktray;
}

Bool configureGeneralSettingsLayerCDRip::GetNTSCSI()
{
	return ntscsi;
}

Bool configureGeneralSettingsLayerCDRip::GetAutoRead()
{
	return autoRead;
}

Bool configureGeneralSettingsLayerCDRip::GetAutoEject()
{
	return autoEject;
}