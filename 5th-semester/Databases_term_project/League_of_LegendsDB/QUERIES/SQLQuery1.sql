--Прелюдия.
CREATE DATABASE League_of_LegendsDB
	ON ( NAME = N'League_of_LegendsDB_Data',
		FILENAME = 'D:\KAI\Базы данных\Моя курсовая работа\League_of_LegendsDB\FILES\League_of_LegendsDB_dat.mdf')
	LOG ON (NAME = N'League_of_LegendsDB_Log',
		FILENAME = 'D:\KAI\Базы данных\Моя курсовая работа\League_of_LegendsDB\FILES\League_of_LegendsDB_log.ldf')
GO

USE League_of_LegendsDB
GO

--Сложные запросы.
SELECT Spells.SpellID, Spells.SpellImage, Spells.SpellName, Spells.SpellDescr, Spells.SpellRecharge, Spells.SpellLine FROM (SpellsAssemblies JOIN Spells ON (SpellsAssemblies.FirstSpell = SpellID OR SpellsAssemblies.SecondSpell = SpellID)) WHERE SpellsAssemblies.HeroID = 1

SELECT TypeRunes.TypeRuneID, TypeRunes.TypeRuneImage, TypeRunes.TypeRuneDescr, TypeRunes.TypeRuneName FROM (RunesAssemblies JOIN TypeRunes ON RunesAssemblies.RuneType = TypeRunes.TypeRuneID) WHERE RunesAssemblies.HeroID = 3
SELECT KeyRunes.KeyRuneID, KeyRunes.TypeRuneID, KeyRunes.KeyRuneImage, KeyRunes.KeyRuneDescr, KeyRunes.KeyRuneName FROM (RunesAssemblies JOIN KeyRunes ON	
	(RunesAssemblies.FirstKeyRune = KeyRunes.KeyRuneID OR 
	RunesAssemblies.SecondKeyRune = KeyRunes.KeyRuneID OR 
	RunesAssemblies.ThirdKeyRune = KeyRunes.KeyRuneID OR 
	RunesAssemblies.FourthKeyRune = KeyRunes.KeyRuneID)) WHERE RunesAssemblies.HeroID = 3 
SELECT AdditionalRunes.AdditionalRuneID, AdditionalRunes.TypeRuneID, AdditionalRunes.AdditionalRuneImage, AdditionalRunes.AdditionalRuneDescr, AdditionalRunes.AdditionalRuneName FROM (RunesAssemblies JOIN AdditionalRunes ON	
	(RunesAssemblies.FirstAdditionalRune = AdditionalRunes.AdditionalRuneID OR
	RunesAssemblies.SecondAdditionalRune = AdditionalRunes.AdditionalRuneID)) WHERE RunesAssemblies.HeroID = 3
SELECT AdaptiveRunes.AdaptiveRuneID, AdaptiveRunes.AdaptiveRuneImage, AdaptiveRunes.AdaptiveRuneDescr, AdaptiveRunes.AdaptiveRuneName FROM (RunesAssemblies JOIN AdaptiveRunes ON
	(RunesAssemblies.FirstAdaptiveRune = AdaptiveRunes.AdaptiveRuneID OR
	RunesAssemblies.SecondAdaptiveRune = AdaptiveRunes.AdaptiveRuneID OR
	RunesAssemblies.ThirdAdaptiveRune = AdaptiveRunes.AdaptiveRuneID)) WHERE RunesAssemblies.HeroID = 3
--Создание таблиц.
CREATE TABLE Heroes
	(HeroID int IDENTITY NOT NULL,
	HeroName varchar(20) NOT NULL,
	HeroImage varbinary(max) NOT NULL,
	HeroHistory text NOT NULL,
	HeroSkillsDescr text NOT NULL,
	HeroType int NOT NULL,
	PRIMARY KEY (HeroID),
	UNIQUE(HeroName, HeroType))
CREATE TABLE HeroTypes
	(TypeID int IDENTITY NOT NULL,
	TypeName varchar(10) NOT NULL UNIQUE,
	PRIMARY KEY (TypeID))
CREATE TABLE HeroInformation
	(HeroID int NOT NULL,
	SkillsCombination text NULL DEFAULT '-',
	SkillsTree text NULL DEFAULT '-',
	SkillsRecharge text NOT NULL,
	PRIMARY KEY (HeroID))
CREATE TABLE SpellsAssemblies
	(SpellsAssemblyID int IDENTITY NOT NULL,
	HeroID int NOT NULL,
	FirstSpell int NOT NULL,
	SecondSpell int NOT NULL,
	PRIMARY KEY (SpellsAssemblyID))
CREATE TABLE Spells
	(SpellID int IDENTITY NOT NULL,
	SpellImage varbinary(max) NOT NULL,
	SpellName varchar(25) NOT NULL UNIQUE,
	SpellDescr text NOT NULL,
	SpellRecharge varchar(10) NOT NULL,
	SpellLine text NULL DEFAULT '-',
	PRIMARY KEY (SpellID))
CREATE TABLE ItemsAssemblies
	(ItemsAssemblyID int IDENTITY NOT NULL,
	HeroID int NOT NULL,
	FirstItem int NOT NULL,
	SecondItem int NOT NULL,
	ThirdItem int NOT NULL,
	FourthItem int NOT NULL,
	FifthItem int NOT NULL,
	SixthItem int NOT NULL,
	PRIMARY KEY (ItemsAssemblyID))
CREATE TABLE Items
	(ItemID int IDENTITY NOT NULL,
	ItemImage varbinary(max) NOT NULL,
	ItemDescr text NULL DEFAULT '-',
	ActiveCharacteristics text NULL DEFAULT '-',
	PassiveCharacteristics text NULL DEFAULT '-',
	GameStage text NULL DEFAULT '-',
	ItemType int NOT NULL,
	ItemCost int NOT NULL,
	ItemName varchar(30) NOT NULL UNIQUE,
	PRIMARY KEY (ItemID))
CREATE TABLE RunesAssemblies
	(RunesAssemblyID int IDENTITY NOT NULL,
	HeroID int NOT NULL,
	RuneType int NOT NULL,
	FirstKeyRune int NOT NULL,
	SecondKeyRune int NOT NULL,
	ThirdKeyRune int NOT NULL,
	FourthKeyRune int NOT NULL,
	FirstAdditionalRune int NOT NULL,
	SecondAdditionalRune int NOT NULL,
	FirstAdaptiveRune int NOT NULL,
	SecondAdaptiveRune int NOT NULL,
	ThirdAdaptiveRune int NOT NULL,
	PRIMARY KEY (RunesAssemblyID))
CREATE TABLE TypeRunes
	(TypeRuneID int IDENTITY NOT NULL,
	TypeRuneImage varbinary(max) NOT NULL,
	TypeRuneDescr text NOT NULL,
	TypeRuneName varchar(30) NOT NULL UNIQUE,
	PRIMARY KEY (TypeRuneID))
CREATE TABLE KeyRunes
	(KeyRuneID int IDENTITY NOT NULL,
	TypeRuneID int NOT NULL,
	KeyRuneImage varbinary(max) NOT NULL,
	KeyRuneDescr text NOT NULL,
	KeyRuneName varchar(50) NOT NULL UNIQUE,
	PRIMARY KEY (KeyRuneID))
CREATE TABLE AdditionalRunes
	(AdditionalRuneID int IDENTITY NOT NULL,
	TypeRuneID int NOT NULL,
	AdditionalRuneImage varbinary(max) NOT NULL,
	AdditionalRuneDescr text NOT NULL,
	AdditionalRuneName varchar(50) NOT NULL UNIQUE,
	PRIMARY KEY (AdditionalRuneID))
CREATE TABLE AdaptiveRunes
	(AdaptiveRuneID int IDENTITY NOT NULL,
	AdaptiveRuneImage varbinary(max) NOT NULL,
	AdaptiveRuneDescr text NOT NULL,
	AdaptiveRuneName varchar(30) NOT NULL,
	PRIMARY KEY (AdaptiveRuneID))


CREATE TABLE Admins
	(AdminID int IDENTITY NOT NULL,
	AdminPass varchar(40) NOT NULL UNIQUE,
	PRIMARY KEY (AdminID))

--Удаление таблиц.
DROP TABLE Heroes
DROP TABLE HeroTypes
DROP TABLE HeroInformation
DROP TABLE SpellsAssemblies
DROP TABLE Spells
DROP TABLE ItemsAssemblies
DROP TABLE Items
DROP TABLE RunesAssemblies
DROP TABLE TypeRunes
DROP TABLE KeyRunes
DROP TABLE AdditionalRunes
DROP TABLE AdaptiveRunes

DROP TABLE Admins

ALTER TABLE Heroes
	ADD CONSTRAINT FK_HeroType_TypeID
	FOREIGN KEY (HeroType) REFERENCES HeroTypes(TypeID)

ALTER TABLE HeroInformation
	ADD CONSTRAINT FK_HeroID_HeroID
	FOREIGN KEY (HeroID) REFERENCES Heroes(HeroID)

ALTER TABLE ItemsAssemblies
	ADD CONSTRAINT FK_ItemHeroID_HeroID
	FOREIGN KEY (HeroID) REFERENCES HeroInformation(HeroID)
ALTER TABLE SpellsAssemblies
	ADD CONSTRAINT FK_SpellHeroID_HeroID
	FOREIGN KEY (HeroID) REFERENCES HeroInformation(HeroID)
ALTER TABLE RunesAssemblies
	ADD CONSTRAINT FK_RuneHeroID_HeroID
	FOREIGN KEY (HeroID) REFERENCES HeroInformation(HeroID)

ALTER TABLE SpellsAssemblies
	ADD CONSTRAINT FK_FirstSpell_SpellID
	FOREIGN KEY (FirstSpell) REFERENCES Spells(SpellID)
ALTER TABLE SpellsAssemblies
	ADD CONSTRAINT FK_SecondSpell_SpellID
	FOREIGN KEY (SecondSpell) REFERENCES Spells(SpellID)

ALTER TABLE Items
	ADD CONSTRAINT FK_ItemType_TypeName
	FOREIGN KEY (ItemType) REFERENCES HeroTypes(TypeID) 

ALTER TABLE ItemsAssemblies
	ADD CONSTRAINT FK_FirstItem_ItemID
	FOREIGN KEY (FirstItem) REFERENCES Items(ItemID)
ALTER TABLE ItemsAssemblies
	ADD CONSTRAINT FK_SecondItem_ItemID
	FOREIGN KEY (SecondItem) REFERENCES Items(ItemID)
ALTER TABLE ItemsAssemblies
	ADD CONSTRAINT FK_ThirdItem_ItemID
	FOREIGN KEY (ThirdItem) REFERENCES Items(ItemID)
ALTER TABLE ItemsAssemblies
	ADD CONSTRAINT FK_FourthItem_ItemID
	FOREIGN KEY (FourthItem) REFERENCES Items(ItemID)
ALTER TABLE ItemsAssemblies
	ADD CONSTRAINT FK_FifthItem_ItemID
	FOREIGN KEY (FifthItem) REFERENCES Items(ItemID)
ALTER TABLE ItemsAssemblies
	ADD CONSTRAINT FK_SixthItem_ItemID
	FOREIGN KEY (SixthItem) REFERENCES Items(ItemID)

ALTER TABLE RunesAssemblies
	ADD CONSTRAINT FK_FirstKeyRune_KeyRuneID
	FOREIGN KEY (FirstKeyRune) REFERENCES KeyRunes(KeyRuneID)
ALTER TABLE RunesAssemblies
	ADD CONSTRAINT FK_SecondKeyRune_KeyRuneID
	FOREIGN KEY (SecondKeyRune) REFERENCES KeyRunes(KeyRuneID)
ALTER TABLE RunesAssemblies
	ADD CONSTRAINT FK_ThirdKeyRune_KeyRuneID
	FOREIGN KEY (ThirdKeyRune) REFERENCES KeyRunes(KeyRuneID)
ALTER TABLE RunesAssemblies
	ADD CONSTRAINT FK_FourthKeyRune_KeyRuneID
	FOREIGN KEY (FourthKeyRune) REFERENCES KeyRunes(KeyRuneID)

ALTER TABLE RunesAssemblies
	ADD CONSTRAINT FK_FirstAdditionalRune_AdditionalRuneID
	FOREIGN KEY (FirstAdditionalRune) REFERENCES AdditionalRunes(AdditionalRuneID)
ALTER TABLE RunesAssemblies
	ADD CONSTRAINT FK_SecondAdditionalRune_AdditionalRuneID
	FOREIGN KEY (SecondAdditionalRune) REFERENCES AdditionalRunes(AdditionalRuneID)

ALTER TABLE RunesAssemblies
	ADD CONSTRAINT FK_FirstAdaptiveRune_AdaptiveRuneID
	FOREIGN KEY (FirstAdaptiveRune) REFERENCES AdaptiveRunes(AdaptiveRuneID)
ALTER TABLE RunesAssemblies
	ADD CONSTRAINT FK_SecondAdaptiveRune_AdaptiveRuneID
	FOREIGN KEY (SecondAdaptiveRune) REFERENCES AdaptiveRunes(AdaptiveRuneID)
ALTER TABLE RunesAssemblies
	ADD CONSTRAINT FK_ThirdAdaptiveRune_AdaptiveRuneID
	FOREIGN KEY (ThirdAdaptiveRune) REFERENCES AdaptiveRunes(AdaptiveRuneID)

ALTER TABLE KeyRunes
	ADD CONSTRAINT FK_TypeRuneID_TypeRunesID
	FOREIGN KEY(TypeRuneID) REFERENCES TypeRunes(TypeRuneID)
ALTER TABLE AdditionalRunes
	ADD CONSTRAINT FK_Additional_TypeRuneID_TypeRunesID
	FOREIGN KEY(TypeRuneID) REFERENCES TypeRunes(TypeRuneID)
ALTER TABLE RunesAssemblies
	ADD CONSTRAINT FK_RuneType_TypeRuneID
	FOREIGN KEY(RuneType) REFERENCES TypeRunes(TypeRuneID)

INSERT INTO Admins(AdminPass)
VALUES
('LOL_admin_guide')

