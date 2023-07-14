#ifndef MYFUNCS_H_
#define MYFUNCS_H_

std::string selectFile(Blank blank, const std::string defaultPath);
bool initStr(Select select, std::istream& f, std::string& subsequence, double& NM);
void result(std::ostream& f, double NM, std::string strOut);
bool getNext();
unsigned char get_0_1();
double getLength();
std::string CheckStrLength(double NM);

#endif /*MYFUNCS_H_*/
