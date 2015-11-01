"use strict;"

BoardManager.prototype.boardList = [
	{
		shortName: "stm32dfu",
		name: "STM32 in DFU Mode",
		vendorId: 0x0483,
		productId: 0xdf11,
		boardType: 0,
		boardRevision: 0
	},
	{
		shortName: "pipxtreme",
		name: "PipXtreme",
		vendorId: 0x20a0,
		productId: 0x415c,
		boardType: 0x03,
		boardRevision: 0x01,
		arch: "stm32f1",
		flashLayout: {
			bootloaderBase: 0x08000000,
			bootloaderSize: 0x00003000,
			firmwareBase: 0x08003000,
			firmwareSize: 0x00019000,
			eepromBase: 0x0801C000,
			eepromSize: 0x00004000
		}
	},
	{
		shortName: "cc3d",
		name: "CC3D",
		vendorId: 0x20a0,
		productId: 0x415b,
		boardType: 0x04,
		boardRevision: 0x02,
		arch: "stm32f1",
		flashLayout: {
			bootloaderBase: 0x08000000,
			bootloaderSize: 0x00003000,
			firmwareBase: 0x08003000,
			firmwareSize: 0x0001D000
		}
	},
	{
		shortName: "coptercontrol",
		name: "CopterControl",
		vendorId: 0x20a0,
		productId: 0x415b,
		boardType: 0x04,
		boardRevision: 0x01,
		arch: "stm32f1",
		flashLayout: {
			bootloaderBase: 0x08000000,
			bootloaderSize: 0x00003000,
			firmwareBase: 0x08003000,
			firmwareSize: 0x0001D000
		}
	},
	{
		shortName: "revomini",
		name: "Revo Mini",
		vendorId: 0x20a0,
		productId: 0x415e,
		boardType: 0x09,
		boardRevision: 0x03,
		arch: "stm32f4",
		flashLayout: {
			bootloaderBase: 0x08000000,
			bootloaderSize: 0x00008000,
			firmwareBase: 0x08020000,
			firmwareSize: 0x00060000
		}
	},
	{
		shortName: "sparky",
		name: "Sparky1",
		vendorId: 0x20a0,
		productId: 0x41d0,
		boardType: 0x88,
		boardRevision: 0x02,
		arch: "stm32f3",
		flashLayout: {
			bootloaderBase: 0x08000000,
			bootloaderSize: 0x00004000,
			firmwareBase: 0x0800C000,
			firmwareSize: 0x00034000,
			eepromBase: 0x08004000,
			eepromSize: 0x00008000
		}
	},
	{
		shortName: "sparky2",
		name: "Sparky2",
		vendorId: 0x0fda,
		productId: 0x0100,
		boardType: 0x92,
		boardRevision: 0x01,
		arch: "stm32f4",
		flashLayout: {
			bootloaderBase: 0x08000000,
			bootloaderSize: 0x00008000,
			firmwareBase: 0x08020000,
			firmwareSize: 0x00060000
		}
	},
	{
		shortName: "flyingf3",
		name: "FlyingF3",
		vendorId: 0x20a0,
		productId: 0x4195,
		boardType: 0x82,
		boardRevision: 0x01,
		arch: "stm32f3",
		flashLayout: {
			bootloaderBase: 0x08000000,
			bootloaderSize: 0x00004000,
			firmwareBase: 0x0800C000,
			firmwareSize: 0x00034000,
			eepromBase: 0x08004000,
			eepromSize: 0x00008000
		}
	},
	{
		shortName: "flyingf4",
		name: "FlyingF4",
		vendorId: 0x20a0,
		productId: 0x4195,
		boardType: 0x84,
		boardRevision: 0x01,
		arch: "stm32f4",
		flashLayout: {
			bootloaderBase: 0x08000000,
			bootloaderSize: 0x00008000,
			firmwareBase: 0x08020000,
			firmwareSize: 0x00040000,
		}
	},
	{
		shortName: "discof4",
		name: "DiscoveryF4",
		vendorId: 0x20a0,
		productId: 0x4195,
		boardType: 0x85,
		boardRevision: 0x01,
		arch: "stm32f4",
		flashLayout: {
			bootloaderBase: 0x08000000,
			bootloaderSize: 0x00008000,
			firmwareBase: 0x08020000,
			firmwareSize: 0x00040000,
			eepromBase: 0x08008000,
			eepromSize: 0x00008000
		}
	},
	{
		shortName: "colibri",
		name: "Colibri",
		vendorId: 0x20a0,
		productId: 0x4235,
		boardType: 0x91,
		boardRevision: 0x01,
		arch: "stm32f4",
		flashLayout: {
			bootloaderBase: 0x08000000,
			bootloaderSize: 0x00008000,
			firmwareBase: 0x08020000,
			firmwareSize: 0x00040000
		}
	},
	{
		shortName: "aq32",
		name: "AeroQuad32",
		vendorId: 0x20a0,
		productId: 0x4284,
		boardType: 0x94,
		boardRevision: 0x01,
		arch: "stm32f4",
		flashLayout: {
			bootloaderBase: 0x08000000,
			bootloaderSize: 0x00008000,
			firmwareBase: 0x08020000,
			firmwareSize: 0x00060000
		}
	},
	{
		shortName: "quanton",
		name: "Quanton",
		vendorId: 0x0fda,
		productId: 0x0100,
		boardType: 0x86,
		boardRevision: 0x01,
		arch: "stm32f4",
		flashLayout: {
			bootloaderBase: 0x08000000,
			bootloaderSize: 0x00008000,
			firmwareBase: 0x08020000,
			firmwareSize: 0x00060000
		}
	},
	{
		shortName: "brain",
		name: "BrainFPV",
		vendorId: 0x20a0,
		productId: 0x4242,
		boardType: 0x8a,
		boardRevision: 0x01,
		arch: "stm32f4",
		flashLayout: {
			bootloaderBase: 0x08000000,
			bootloaderSize: 0x00008000,
			firmwareBase: 0x08020000,
			firmwareSize: 0x000E0000
		}
	},
	{
		shortName: "naze",
		name: "OpenNaze",
		boardType: 0xa0,
		boardRevision: 0x01,
		arch: "stm32f1",
		flashLayout: {
			firmwareBase: 0x08000000,
			firmwareSize: 0x0001D000,
			eepromBase: 0x0801D000,
			eepromSize: 0x00003000
		}
	}
];
