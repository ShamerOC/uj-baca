// Krzysztof Wydrzynski
bool printedNumber = false;

int whichOneIsBigger(std::string str1, std::string str2, int val = 0) {
    if ((str1[val] == '-' || str1[val] == '+') && (str2[val] == '-' || str2[val] == '+')) return whichOneIsBigger(str1, str2, val + 1);
    if (val >= str1.size()) return 0;
    if ((int)str1[val] - '0' < (int)str2[val] - '0') return 2;
    if ((int)str1[val] - '0' > (int)str2[val] - '0') return 1;
    return whichOneIsBigger(str1, str2, val + 1);
}

void makeStringsSameSize(std::string& str1, std::string& str2) {
    if (str1.size() < str2.size()) {
        std::string newStr = "";
        if (str1[0] == '-') {
            str1[0] = '0';
            newStr = "-";
            newStr += str1;
            str1 = newStr;
        } else if (str1[0] == '+') {
            str1[0] = '0';
            newStr = "+";
            newStr += str1;
            str1 = newStr;
        } else {
            newStr += "0";
            newStr += str1;
            str1 = newStr;
        }
        makeStringsSameSize(str1, str2);
    } else if (str1.size() > str2.size()) {
        std::string newStr = "";
        if (str2[0] == '-') {
            str2[0] = '0';
            newStr = "-";
            newStr += str2;
            str2 = newStr;
        } else if (str2[0] == '+') {
            str2[0] = '0';
            newStr = "+";
            newStr += str2;
            str2 = newStr;
        } else {
            newStr += "0";
            newStr += str2;
            str2 = newStr;
        }
        makeStringsSameSize(str1, str2);
    } else {
        return;
    }
}

int absolute (int number) {
    if (number < 0) {
        number *= -1;
    }
    return number;
}

void addSign (std::string& str1) {
    if (str1[0] != '+' && str1[0] != '-') {
        std::string sign = "+";
        sign += str1;
        str1 = sign;
    }
}

bool isStringOnlyZero(std::string str, int i = 0) {
    if (i >= str.size()) return true;
    if (str[i] == '-' || str[i] == '+') isStringOnlyZero(str, i + 1);
    if (str[i] != '0') return false;
    return isStringOnlyZero(str, i + 1);
}

void deleteAdditionalZero (std::string& str1) {
    if (isStringOnlyZero(str1)) {
        str1 = "0";
        return;
    }
    if (str1[0] == '-' || str1[0] == '+') {
        std::string str = str1.substr(1);
        std::size_t found = str.find_first_not_of('0');
        if (found == -1) {
            str1 = "0";
            return;
        }
        str = str.substr(found);
        std::string newStr = "";
        newStr += str1[0];
        newStr += str;
        str1 = newStr;
        return;
    }
    std::size_t found = str1.find_first_not_of('0');
    if (found == -1) {
        str1 = "0";
        return;
    }
    str1 = str1.substr(found);
}

void moveLeftByAmmount (std::string& str, int amm, int i = 0) {
    if (i == amm) return;
    str += '0';
    moveLeftByAmmount(str, amm, i + 1);
}

std::string addPositiveStrings(std::string str1, std::string str2, int number, int carry = 0) {
    if (number < 0) return "";
    else if (number == 0 && (str1[0] == '+' || str2[0] == '+' || str1[0] == '-' || str2[0] == '-')) return "";
    std::string result;
    int res = (((int)str1[number] - '0') + ((int)str2[number] - '0')) + carry;
    carry = res / 10;
    result = addPositiveStrings(str1, str2, number - 1, carry);

    if ((number == 0 && carry != 0) || (number == 1 && (str1[0] == '+' || str2[0] == '+' || str1[0] == '-' || str2[0] == '-'))) result.push_back((char)carry + '0');
    result.push_back(((char)res % 10) + '0');
    return result;
}

std::string subtractPositiveStringsRecurention(std::string str1, std::string str2, int number, int borrow = 0) {
    if (number < 0) return "";
    else if (number == 0 && (str1[0] == '+' || str2[0] == '+' || str1[0] == '-' || str2[0] == '-')) return "";
    std::string result;

    int res = ((((int)str1[number] - '0') - borrow) - ((int)str2[number] - '0'));
    if (res < 0) {
        res += 10;
        borrow = 1;
    } else {
        borrow = 0;
    }

    result = subtractPositiveStringsRecurention(str1, str2, number - 1, borrow);

    if (res == 0 && !printedNumber) {
        return result;
    } else {
        printedNumber = true;
    }
    result.push_back(((char)res) + '0');

    return result;
}

std::string subtractPositiveStrings(std::string str1, std::string str2) {
    printedNumber = false;
    std::string result = "";
//    std::cout << "str1: " << str1 << " str2: " << str2 << '\n';
//    makeStringsSameSize(str1, str2);
    int bigger = whichOneIsBigger(str1, str2);
//    std::cout << "bigger: " << bigger << '\n';
//    if (str1[0] == '-') {
//        bigger = 2;
//    } else {
//        bigger = 1;
//    }
    if (bigger == 1 && str1[0] == '-') {
        str1[0] = '0';
        result += "-";
    } else if (bigger == 1 && str1[0] != '-') {
        str2[0] = '0';
        result = "";
    } else if (bigger == 2 && str2[0] != '-') {
        str1[0] = '0';
        std::string swap = str1;
        str1 = str2;
        str2 = swap;
        result = "";
    } else if (bigger == 2 && str2[0] == '-') {
        str2[0] = '0';
        std::string swap = str1;
        str1 = str2;
        str2 = swap;
        result = "-";
    }
    if (str1[0] == '+') str1[0] = '0';
    if (str2[0] == '+') str2[0] = '0';
//    std::cout << str1 << " " << str2;
    result += subtractPositiveStringsRecurention(str1, str2, str1.size() - 1);

    if (result.empty()) result = "0";
//    std::cout << "res: " << result << '\n';
    return result;
}

std::string multByChar (std::string str1, char mult, int i, std::string result = "", int carry = 0) {
    if (i < 1) return result;
    if (mult == '0') return "0";
    int res = (str1[i] - '0') * (mult - '0') + carry;
//    std::cout << res << " = " << str1[i] - '0' << " * " << mult - '0' << " + " << carry << '\n';
    carry = res / 10;
    result = multByChar(str1, mult, i - 1, result, carry);
    if ((i == 0 && carry != 0) || (i == 1 && (str1[0] == '+' || str1[0] == '-'))) result.push_back((char)carry + '0');
    result += (char)(res % 10) + '0';
//    std::cout << res << " ";
    return result;
}

std::string multI (std::string str1, std::string str2, int i, std::string res = "") {
    if (i <= 0) return res;
    char mult = str2[i];
    std::string resMult = multByChar(str1, mult, str1.size() - 1);
    moveLeftByAmmount(resMult, absolute(i - (str2.size() - 1)));
    makeStringsSameSize(resMult, res);
    res = addPositiveStrings(res, resMult, res.size() - 1);
    return multI(str1, str2, i - 1, res);
}

std::string multiply (std::string str1, std::string str2) {
    std::string sign = "";
    addSign(str1);
    addSign(str2);
    makeStringsSameSize(str1, str2);
    if ((str1[0] == '-' && str2[0] != '-') || (str1[0] != '-' && str2[0] == '-')) {
        sign = "-";
    }
    sign += multI(str1, str2, str1.size() - 1);
    deleteAdditionalZero(sign);
    return sign;
}



std::string SumI (int howManyDataSets, const std::string* dataSet, std::string sum = "0" , int i = 0) {
    if (i >= howManyDataSets) return sum;
    std::string str = dataSet[i];
    addSign(sum);
    addSign(str);
    makeStringsSameSize(sum, str);
    if ((str[0] == '-' && sum[0] != '-') || (str[0] != '-' && sum[0] == '-')) {
        sum = subtractPositiveStrings(sum, str);
    } else {
        std::string newStr = "";
        if (sum[0] == '-' && str[0] == '-') {
            newStr = "-";
        }
        sum = addPositiveStrings(sum, str, sum.size() - 1);
        newStr += sum;
        sum = newStr;
    }
    deleteAdditionalZero(sum);
    return SumI (howManyDataSets, dataSet, sum, i + 1);
}

std::string Sum (int howManyDataSets, const std::string* dataSet) {
    return SumI (howManyDataSets, dataSet);
}

std::string MultIt(int howManyDataSets, const std::string* dataSet, std::string res = "1" , int i = 0) {
    if (i  >= howManyDataSets) return res;
    std::string str = dataSet[i];
    deleteAdditionalZero(res);
    res = multiply(res, dataSet[i]);
    return MultIt (howManyDataSets, dataSet, res, i + 1);
}

std::string Mult (int howManyDataSets, const std::string* dataSet) {
    return MultIt (howManyDataSets, dataSet);
}

std::string SumVa(va_list args, std::string res, int i) {
    if (i <= 0) return res;
    std::string temp = va_arg(args, char*);
//    std::cout << temp << " ";
    addSign(res);
    addSign(temp);
    makeStringsSameSize(res, temp);
//    std::cout << "after: first: " << sum << " second: " << str << '\n';
    if ((temp[0] == '-' && res[0] != '-') || (temp[0] != '-' && res[0] == '-')) {
        res = subtractPositiveStrings(res, temp);
    } else {
        std::string newStr = "";
        if (res[0] == '-' && temp[0] == '-') {
            newStr = "-";
        }
        res = addPositiveStrings(res, temp, res.size() - 1);
        newStr += res;
        res = newStr;
    }
    deleteAdditionalZero(res);
    return SumVa(args, res, i - 1);

}

std::string Sum (int howManyDataSets, ...) {

    va_list args;

    va_start (args, howManyDataSets);

    std::string val = SumVa(args, "0", howManyDataSets);

    va_end(args);
    return val;

}

void Sum (std::string* str, int howManyDataSets, const std::string* dataSet) {
    *str =  SumI (howManyDataSets, dataSet);
}

void Sum (std::string* str, int howManyDataSets, ...) {
    va_list args;

    va_start (args, howManyDataSets);

    std::string val = SumVa(args, "0", howManyDataSets);

    va_end(args);
    *str = val;
}

void Sum (std::string& str, int howManyDataSets, const std::string* dataSet) {
    str =  SumI (howManyDataSets, dataSet);
}

void Sum (std::string& str, int howManyDataSets, ...) {
    va_list args;

    va_start (args, howManyDataSets);

    std::string val = SumVa(args, "0", howManyDataSets);

    va_end(args);
    str = val;
}

std::string MultVa (va_list args, std::string res, int i) {
    if (i <= 0) return res;
    std::string temp = va_arg(args, char*);

    deleteAdditionalZero(res);
    res = multiply(res, temp);
    return MultVa (args, res, i - 1);
}

std::string Mult (int howManyDataSets, ...) {
    va_list args;

    va_start (args, howManyDataSets);

    std::string val = MultVa(args, "1", howManyDataSets);

    va_end(args);
    return val;
}

void Mult (std::string* res, int howManyDataSets, const std::string* dataSet) {
    *res = MultIt (howManyDataSets, dataSet);
}

void Mult (std::string* res, int howManyDataSets, ...) {
    va_list args;

    va_start (args, howManyDataSets);

    std::string val = MultVa(args, "1", howManyDataSets);

    va_end(args);
    *res = val;
}

void Mult (std::string& res, int howManyDataSets, const std::string* dataSet) {
    res = MultIt (howManyDataSets, dataSet);
}

void Mult (std::string& res, int howManyDataSets, ...) {
    va_list args;

    va_start (args, howManyDataSets);

    std::string val = MultVa(args, "1", howManyDataSets);

    va_end(args);
    res = val;
}

std::string Operation (std::string (*function)(int, const std::string*), int howManyDataSets, const std::string* dataSet) {
    return function(howManyDataSets, dataSet);
}

void createDataSet(va_list args, int i, std::string* arr, int j = 0) {
    if (i <= 0) return;
    std::string temp = va_arg(args, char*);
    arr[i - 1] = temp;
    createDataSet(args, i - 1, arr);
}

std::string Operation (std::string (*function)(int, const std::string*), int howManyDataSets, ...) {
    std::string* dataSet = new std::string[howManyDataSets];
    va_list args;
    va_start(args, howManyDataSets);
    createDataSet(args, howManyDataSets, dataSet);
    va_end(args);
    std::string res = function(howManyDataSets, dataSet);
    delete[] dataSet;
    return res;
}

void Operation (std::string* result, std::string (*function)(int, const std::string*), int howManyDataSets, ...) {
    std::string* dataSet = new std::string[howManyDataSets];
    va_list args;
    va_start(args, howManyDataSets);
    createDataSet(args, howManyDataSets, dataSet);
    va_end(args);
    std::string res = function(howManyDataSets, dataSet);
    delete[] dataSet;
    *result = res;
}

void Operation (std::string* result, std::string (*function)(int, const std::string*), int howManyDataSets, const std::string* dataSet) {
    *result = function(howManyDataSets, dataSet);
}

void Operation (std::string& result, void (*function)(std::string*, int, const std::string*), int howManyDataSets, ...) {
    std::string* pointer = new std::string();
    std::string* dataSet = new std::string[howManyDataSets];
    va_list args;
    va_start(args, howManyDataSets);
    createDataSet(args, howManyDataSets, dataSet);
    va_end(args);
    function(pointer, howManyDataSets, dataSet);
    result = *pointer;
    delete[] dataSet;
    delete pointer;
}

void Operation (std::string& result, void (*function)(std::string*, int, const std::string*), int howManyDataSets, const std::string* dataSet) {
    std::string* pointer = new std::string();
    function(pointer, howManyDataSets, dataSet);
    result = *pointer;
    delete pointer;
}