/*****************************************************************************

		Copyright (c) My Company

 Project:  DB
 FileName: DB.PRO
 Purpose: No description
 Written by: Visual Prolog
 Comments:
******************************************************************************/

include "db.inc"

domains
	TRecording = STRING
	TDisk = STRING
	TAuthor = STRING
	TSong = STRING

facts
	item(TRecording, TDisk, TAuthor, TSong)

predicates

  nondeterm switch(INTEGER)
  nondeterm repeat

clauses

  repeat.
  repeat:-repeat.

  switch(Case) :- Case = '0', write("The program is complited. Good Bye!"), nl.
  switch(Case) :- Case = '1',
  	write('\10', "-[ ADD ]-------------------"),
  	write('\10', "TRecording: "), readln(TRecording),
  	write('\10', "TDisk: "), readln(TDisk),
  	write('\10', "TAuthor: "), readln(TAuthor),
  	write('\10', "TSong: "), readln(TSong),
  	assert(item(TRecording, TDisk, TAuthor, TSong)), fail.
  switch(Case) :- Case = '2',
  	write('\10', "-[ DELETE ]-------------------"),
  	write('\10', "TRecording: "), readln(TRecording),
  	write('\10', "TDisk: "), readln(TDisk),
  	write('\10', "TAuthor: "), readln(TAuthor),
  	write('\10', "TSong: "), readln(TSong),
  	retract(item(TRecording, TDisk, TAuthor, TSong)), fail.
  switch(Case) :- Case = '3',
  	write('\10', "-[ EDIT ]-------------------"),
  	write('\10', "REPLACE ITEM: "),
  	write('\10', "TRecording: "), readln(TRecording),
  	write('\10', "TDisk: "), readln(TDisk),
  	write('\10', "TAuthor: "), readln(TAuthor),
  	write('\10', "TSong: "), readln(TSong),
  	retract(item(TRecording, TDisk, TAuthor, TSong)),
  	write('\10', "TRecording: "), readln(TRecording1),
  	write('\10', "TDisk: "), readln(TDisk1),
  	write('\10', "TAuthor: "), readln(TAuthor1),
  	write('\10', "TSong: "), readln(TSong1),
  	assert(item(TRecording1, TDisk1, TAuthor1, TSong1)), fail.
  switch(Case) :- Case = '4',
  	write('\10', "-[ SAVING ]-------------------"),
  	save("D:\\KAI\\Functional and Logic Programming\\Laba_8\\db.txt"),
  	write('\10', "DB saved in file db.txt "), nl, fail.
  switch(Case) :- Case = '5',
  	write('\10', "-[ LOADING ]-------------------"),
  	retractall(item(_,_,_,_)),
  	consult("D:\\KAI\\Functional and Logic Programming\\Laba_8\\db.txt"),
  	write('\10', "DB loaded from file db.txt "), nl, fail.
  switch(Case) :- Case = '6',
  	write('\10', "-[ PRINT ]-------------------"),
  	item(TRecording, TDisk, TAuthor, TSong),
  	write('\10', "TRecording: ", TRecording),
	write('\10', "TDisk: ", TDisk),
	write('\10', "TAuthor: ", TAuthor),
	write('\10', "TSong: ", TSong),
  	write('\10', "-----------------------------"), fail.
	
goal
	repeat,
	write('\10',"-[ MENU ]------------------"),
        write('\10',"[1]  ADD"),
        write('\10',"[2]  DELETE"),
        write('\10',"[3]  EDIT"),
        write('\10',"[4]  SAVE"),
        write('\10',"[5]  LOAD"),
        write('\10',"[6]  PRINT"),
        write('\10',"[0]  EXIT"),
        readchar(Case), nl, switch(Case),!.