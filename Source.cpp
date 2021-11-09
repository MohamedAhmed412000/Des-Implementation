#include "iostream"
#include "string"

using namespace std;

// Convert from binary to hexadecimal and the opposite
string hex2bin(string input){
	string output = "";
	for (int i = 0; i < input.length(); i++){	
		switch (input[i]){
		case '0':
			output += "0000";
			break;
		case '1':
			output += "0001";
			break;
		case '2':
			output += "0010";
			break;
		case '3':
			output += "0011";
			break;
		case '4':
			output += "0100";
			break;
		case '5':
			output += "0101";
			break;
		case '6':
			output += "0110";
			break;
		case '7':
			output += "0111";
			break;
		case '8':
			output += "1000";
			break;
		case '9':
			output += "1001";
			break;
		case 'A':
			output += "1010";
			break;
		case 'B':
			output += "1011";
			break;
		case 'C':
			output += "1100";
			break;
		case 'D':
			output += "1101";
			break;
		case 'E':
			output += "1110";
			break;
		case 'F':
			output += "1111";
			break;
		default:
			break;
		}
	}
	return output;
}
string bin2hex(string num){
	string output = "";
	for (int i = 0; i < num.length(); i += 4){
		string str = num.substr(i, 4);
		if (str == "0000")
			output += '0';
		else if (str == "0001")
			output += '1';
		else if (str == "0010")
			output += '2';
		else if (str == "0011")
			output += '3';
		else if (str == "0100")
			output += '4';
		else if (str == "0101")
			output += '5';
		else if (str == "0110")
			output += '6';
		else if (str == "0111")
			output += '7';
		else if (str == "1000")
			output += '8';
		else if (str == "1001")
			output += '9';
		else if (str == "1010")
			output += 'A';
		else if (str == "1011")
			output += 'B';
		else if (str == "1100")
			output += 'C';
		else if (str == "1101")
			output += 'D';
		else if (str == "1110")
			output += 'E';
		else
			output += 'F';
	}
	return output;
}

/* ================== KEY PART =================== */
// Permitation choice 1 (64 => 56)
string PC1 (string input){
	// Convert Key from 64-bits into 56-bits
	string output = "";
	int index[56] = {57, 49, 41, 33, 25, 17, 9, 1,
					 58, 50, 42, 34, 26, 18, 10, 2, 
					 59, 51, 43, 35, 27, 19, 11, 3, 
					 60, 52, 44, 36, 
					 63, 55, 47, 39, 31, 23, 15, 7,
					 62, 54, 46, 38, 30, 22, 14, 6, 
					 61, 53, 45, 37, 29, 21, 13, 5, 
									28, 20, 12, 4};
	for (int i = 0; i < 56; i++)
		output += input[index[i]-1];
	return output;
}
// Shift left with n-bits (56 => 56)
string LSL (string input, int n) {
	string output = input.substr(n, input.length()-n);
	for (int i = 0; i < n; i++)
		output += input[i];
	return output;
}
// Permitation choice 2 (56 => 48)
string PC2_key (string in1, string in2) {
	// convert Key from 56-bits to 48-bits
	string input = in1 + in2, output = "";
	int index[48] = {14, 17, 11, 24, 1, 5,
					 3, 28, 15, 6, 21, 10,
					 23, 19, 12, 4, 26, 8,
					 16, 7, 27, 20, 13, 2,
					 41, 52, 31, 37, 47, 55,
					 30, 40, 51, 45, 33, 48, 
					 44, 49, 39, 56, 34, 53, 
					 46, 42, 50, 36, 29, 32};
	for (int i = 0; i < 48; i++)
		output += input[index[i]-1];
	return output;
}
// Generate all 16 keys for all stages in DES rounds (48-bits)
// Order = True in Encryption
// Order = False in Decryption
string* generate_16keys(string key, bool order){
	string* keys = new string[16];
	int Iter[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
	int ord = !order? 15 : 0;
	key = PC1(key);
	string L_key = key.substr(0, 28), R_key = key.substr(28, 28);
	for (int i = 0; i < 16; i++){
		L_key = LSL(L_key, Iter[i]);
		R_key = LSL(R_key, Iter[i]);
		keys[abs(ord-i)] = PC2_key(L_key, R_key);
	} 
	return keys;
}

/* ================== Data PART =================== */
// Initial permition (64 => 64)
string IP (string input) {
	string output = "";
	int index[64] = {58, 50, 42, 34, 26, 18, 10, 2,
					 60, 52, 44, 36, 28, 20, 12, 4,
					 62, 54, 46, 38, 30, 22, 14, 6,
					 64, 56, 48, 40, 32, 24, 16, 8,
					 57, 49, 41, 33, 25, 17, 9, 1,
					 59, 51, 43, 35, 27, 19, 11, 3, 
					 61, 53, 45, 37, 29, 21, 13, 5, 
					 63, 55, 47, 39, 31, 23, 15, 7};
	for (int i = 0; i < 64; i++)
		output += input[index[i]-1];
	return output;
}
// Expand Right Part (32 => 48)
string EP (string input) {
	string output = "";
	int index[48] = {32, 1, 2, 3, 4, 5,
					 4, 5, 6, 7, 8, 9,
					 8, 9, 10, 11, 12, 13,
					 12, 13, 14, 15, 16, 17,
					 16, 17, 18, 19, 20, 21,
					 20, 21, 22, 23, 24, 25, 
					 24, 25, 26, 27, 28, 29, 
					 28, 29, 30, 31, 32, 1};
	for (int i = 0; i < 48; i++)
		output += input[index[i]-1];
	return output;
}
// Xor any 2 binary strings with any size (48-bits)
string XOR (string in1, string in2){
	string output = "";
	for (int i = 0; i < in1.length(); i++){
		if (in1[i] == in2[i])
			output += '0';
		else
			output += '1';
	}
	return output;
}

// to convrt binary index of s-box to decimal index 
int getIndex(string num){
	if (num.length() == 2){
		if (num == "00")
			return 0;
		else if (num == "01")
			return 1;
		else if (num == "10")
			return 2;
		else
			return 3;
	}
	if (num == "0000")
		return 0;
	else if (num == "0001")
		return 1;
	else if (num == "0010")
		return 2;
	else if (num == "0011")
		return 3;
	else if (num == "0100")
		return 4;
	else if (num == "0101")
		return 5;
	else if (num == "0110")
		return 6;
	else if (num == "0111")
		return 7;
	else if (num == "1000")
		return 8;
	else if (num == "1001")
		return 9;
	else if (num == "1010")
		return 10;
	else if (num == "1011")
		return 11;
	else if (num == "1100")
		return 12;
	else if (num == "1101")
		return 13;
	else if (num == "1110")
		return 14;
	else
		return 15;
}
// to convert decimal value from s-box to binary value
string dec2bin(int num){
	switch (num){
	case 0:
		return "0000";
	case 1:
		return "0001";
	case 2:
		return "0010";
	case 3:
		return "0011";
	case 4:
		return "0100";
	case 5:
		return "0101";
	case 6:
		return "0110";
	case 7:
		return "0111";
	case 8:
		return "1000";
	case 9:
		return "1001";
	case 10:
		return "1010";
	case 11:
		return "1011";
	case 12:
		return "1100";
	case 13:
		return "1101";
	case 14:
		return "1110";
	case 15:
		return "1111";
	default:
		break;
	}
}
// Reduce Right part size (48 => 32)
string S_Box (string input) {
	string output = "";
	int S[8][4][16] = {{{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7}, 
						{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8}, 
						{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0}, 
						{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
					   {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
						{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
						{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
						{13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},
					   {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
						{13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
						{13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
						{1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},
					   {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
						{13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
						{10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
						{3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
					   {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
						{14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
						{4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
						{11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},
					   {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
						{10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
						{9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
						{4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},
					   {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
						{13, 0, 11, 7, 4, 9, 3, 10, 14, 3, 5, 12, 2, 15, 8, 6},
						{1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
						{6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},
					   {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
						{1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
						{7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
						{2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}};
	
	for (int i = 0; i < input.length(); i += 6){
		string str = input.substr(i, 6);
		output += dec2bin(S[i/6][getIndex( string(1, str[0])+str[5] )][ getIndex(str.substr(1, 4)) ]);
	}
	return output;
}
// permition (32-bits)
string P (string input) {
	string output = "";
	int index[32] = {16, 7, 20, 21,
					 29, 12, 28, 17,
					 1, 15, 23, 26,
					 5, 18, 31, 10,
					 2, 8, 24, 14,
					 32, 27, 3, 9, 
					 19, 13, 30, 6, 
					 22, 11, 4, 25};
	for (int i = 0; i < 32; i++)
		output += input[index[i]-1];
	return output;
}
// Inverse initial permition (64-bits)
string Inverse_IP (string input) {
	string output = "";
	int index[64] = {40, 8, 48, 16, 56, 24, 64, 32,
					 39, 7, 47, 15, 55, 23, 63, 31,
					 38, 6, 46, 14, 54, 22, 62, 30,
					 37, 5, 45, 13, 53, 21, 61, 29,
					 36, 4, 44, 12, 52, 20, 60, 28,
					 35, 3, 43, 11, 51, 19, 59, 27, 
					 34, 2, 42, 10, 50, 18, 58, 26, 
					 33, 1, 41, 9, 49, 17, 57, 25};
	for (int i = 0; i < 64; i++)
		output += input[index[i]-1];
	return output;
}
// Apply 1 round of DES Algorithm
string one_round(string data, string key){
	string Rdata = data.substr(32, 32);
	string Lout = Rdata;
	string Ldata = data.substr(0, 32);
	Rdata = EP(Rdata);
	Rdata = XOR(Rdata, key);
	Rdata = S_Box(Rdata);
	Rdata = P(Rdata);
	Rdata = XOR(Rdata, Ldata);
	return Lout + Rdata;
}
// Apply Decrypt or Encrypt by 16 round
// encrypt = True (Encryption)
// encrypt = False (Decryption)
string Cypher(string data, string key, bool encrypt = true){
	data = IP(data);
	string* keys = generate_16keys(key, encrypt);
	for (int i = 0; i < 16; i++)
		data = one_round(data, keys[i]);
	data = data.substr(32, 32) + data.substr(0, 32);
	data = bin2hex(Inverse_IP(data));
	return data;
}


int main(int argc, char** argv){
	 string funType = argv[1], data = hex2bin(argv[2]), key = hex2bin(argv[3]);
	// string funType = "encrypt", data = hex2bin("7A6C731D22347676"), key = hex2bin("1323445A6D788381");
	// string funType = "decrypt", data = hex2bin("7DB033DD14D6F975"), key = hex2bin("1323445A6D788381");
	cout << Cypher(data, key, funType == "encrypt") << endl;
	//system("pause");
	return 0;
}