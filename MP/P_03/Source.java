// Wydrzynski Krzysztof - 4
import java.util.Scanner;

public class Source {
    public static Scanner in = new Scanner(System.in);

    public static void main(String[] args) {
        int dataSetsNumber = in.nextInt();
        for (int i = 0; i < dataSetsNumber; i++) {
            String originalDataType = in.next();
            String input = in.nextLine();
            if (isOnp(originalDataType)) {
                System.out.print("INF: ");
                input = deleteUnwantedCharactersOnp(input);
                char[] data = input.toCharArray();
                onpToInf(data);
            } else {
                System.out.print("ONP: ");
                input = deleteUnwantedCharactersInf(input);
                char[] data = input.toCharArray();
                if (checkInf(data)) {
                    infToOnp(data);
                } else System.out.print("error");
            }
            System.out.println();
        }
    }

    public static boolean isOnp(String str) {
        return str.charAt(0) == 'O';
    }

    public static void infToOnp(char[] data) {
        StackChar stackChar = new StackChar(data.length);

        for (int i = 0; i < data.length; i++) {
            char currentChar = data[i];
            if (isCharSmallLetter(currentChar)) {
                System.out.print(currentChar);
            } else if (isLeftCombineOperator(currentChar)) {
                char lastChar = stackChar.getLastElement();
                if (isLeftCombineOperator(currentChar)) {
                    while (getPriority(currentChar) <= getPriority(lastChar) && getPriority(lastChar) != 100) {
                        System.out.print(lastChar);
                        stackChar.pop();
                        lastChar = stackChar.getLastElement();
                    }
                    stackChar.push(currentChar);
                }
            } else if (isRightCombineOperator(currentChar)) {
                char lastChar = stackChar.getLastElement();
                    while (getPriority(currentChar) < getPriority(lastChar) && getPriority(lastChar) != 100) {
                        System.out.print(lastChar);
                        stackChar.pop();
                        lastChar = stackChar.getLastElement();
                    }
                stackChar.push(currentChar);
            }
            else if (currentChar == ')') {
                currentChar = stackChar.getLastElement();
                while (currentChar != '(') {
                    System.out.print(currentChar);
                    stackChar.pop();
                    currentChar = stackChar.getLastElement();
                }
                stackChar.pop();
            } else if (currentChar == '(') {
                stackChar.push(currentChar);
            }

        }
        stackChar.print();


    }

    public static void onpToInf(char[] data) {
        StackString stack = new StackString(data.length);
        StackInt stackPriority = new StackInt(data.length);
        StringBuilder tmp;
        int operandQuantity = 0;
        int operatorQuantity = 0;


        for (int i = 0; i < data.length; i++) {
            char currentChar = data[i];

            if (isCharSmallLetter(currentChar)) {
                stack.push(currentChar);
                stackPriority.push(getPriority(currentChar));
                operandQuantity++;
            } else {
                tmp = new StringBuilder();
                if (currentChar != '~') {
                    operatorQuantity++;
                    if (currentChar == '=' || currentChar == '^') {
                        if (stackPriority.getLastElement() < getPriority(currentChar)) { // sprawdzamy lewa strone
                            tmp.append('(').append(stack.pop()).append(')');
                        } else {
                            tmp.append(stack.pop());
                        }
                    } else {
                        if (stackPriority.getLastElement() <= getPriority(currentChar)) { // sprawdzamy lewa strone
                            tmp.append('(').append(stack.pop()).append(')');
                        } else {
                            tmp.append(stack.pop());
                        }
                    }
                    stackPriority.pop();
                    String currentTmp = tmp.toString();
                    tmp = new StringBuilder();
                    if (currentChar == '=' || currentChar == '^') {
                        if (stackPriority.getLastElement() <= getPriority(currentChar)) {
                            tmp.append('(').append(stack.pop()).append(')').append(currentChar).append(currentTmp);
                        } else {
                            tmp.append(stack.pop()).append(currentChar).append(currentTmp);
                        }
                    } else {
                        if (stackPriority.getLastElement() < getPriority(currentChar)) {
                            tmp.append('(').append(stack.pop()).append(')').append(currentChar).append(currentTmp);
                        } else {
                            tmp.append(stack.pop()).append(currentChar).append(currentTmp);
                        }
                    }
                } else {
                    if (stackPriority.getLastElement() < getPriority(currentChar)) {
                        tmp.append(currentChar).append('(').append(stack.pop()).append(')');
                    } else {
                        tmp.append(currentChar).append(stack.pop());
                    }
                }
                stackPriority.pop();
                stack.push(tmp.toString());
                stackPriority.push(getPriority(currentChar));
            }
        }
        if (operandQuantity - 1 == operatorQuantity) {
            System.out.print(stack.pop());
        } else {
            System.out.print("error");
        }
    }

    public static boolean checkInf(char[] data) {
        int state = 0;
        int operandCounter = 0;
        int operatorCounter = 0;
        int openBracketCounter = 0;
        int closedBracketCounter = 0;
        char firstBracket = '(';
        char lastBracket = ')';
        boolean previousIsOperator = false;
        for (int i = 0; i < data.length; i++) {
            char currentChar = data[i];
            if (isCharSmallLetter(currentChar)) {
                if (state == 0 || state == 2) {
                    state = 1;
                } else {
                    return false;
                }
                operandCounter++;
            } else if (isTwoArgumentOperator(currentChar)) {
                if (state == 1) {
                    state = 0;
                } else {
                    return false;
                }
                if (currentChar == '=' && previousIsOperator) {
                    return false;
                } else if (currentChar != '=') previousIsOperator = true;
                operatorCounter++;
            } else if (currentChar == '~') {
                if (state == 0 || state == 2) state = 2;
                else return false;
            } else if (currentChar == '(') {
                if (state == 0 || state == 2) state = 0;
                else return false;
                if (closedBracketCounter == 0 && openBracketCounter == 0) firstBracket = currentChar;
                lastBracket = currentChar;
                openBracketCounter++;
            } else if (currentChar == ')') {
                if (state != 1) return false;
                if (closedBracketCounter == 0 && openBracketCounter == 0) firstBracket = currentChar;
                lastBracket = currentChar;
                closedBracketCounter++;
            }
        }
//        System.out.println(state + " " + operandCounter + " " + operatorCounter);
        return state == 1 && closedBracketCounter == openBracketCounter && firstBracket == '(' && lastBracket == ')' && operandCounter - 1 == operatorCounter;
    }

    private static boolean isCharSmallLetter(char character) {
        return ((int)character >= (int) 'a' && (int)character <= (int) 'z');
    }

    private static String deleteUnwantedCharactersInf(String str) {
        String res = "";
        for (int i = 0; i < str.length(); i++) {
            char currentChar = str.charAt(i);
            if (isOperationChar(currentChar) || isCharSmallLetter(currentChar) || currentChar == '(' || currentChar == ')') {
                res += currentChar;
            }
        }
        return res;
    }

    private static String deleteUnwantedCharactersOnp(String str) {
        String res = "";
        for (int i = 0; i < str.length(); i++) {
            char currentChar = str.charAt(i);
            if (isOperationChar(currentChar) || isCharSmallLetter(currentChar)) {
                res += currentChar;
            }
        }
        return res;
    }

    private static int getPriority (char character) {
        switch (character) {
            case '=':
                return 0;
            case '<':
            case '>':
                return 1;
            case '+':
            case '-':
                return 2;
            case '*':
            case '/':
            case '%':
                return 3;
            case '^': return 4;
            case '~': return 5;
        }
        if (isCharSmallLetter(character)) return 6;
        return 100;
    }

    private static boolean isLeftCombineOperator(char character) {
        char[] leftCombineOperators = {'<', '>', '+' , '-' , '*', '/', '%'};
        for (int i = 0; i < 7; i++) {
            if (character == leftCombineOperators[i]) return true;
        }
        return false;
    }

    private static boolean isRightCombineOperator(char character) {
        char[] rightCombineOperators = {'=', '^', '~'};
        for (int i = 0; i < 3; i++) {
            if (character == rightCombineOperators[i]) return true;
        }
        return false;
    }

    private static boolean isOperationChar(char character) {
        char[] allowedCharacters = {'=', '<', '>', '+' , '-', '*', '/', '%', '^', '~'};
        for (int i = 0; i < 10; i++) {
            if (character == allowedCharacters[i]) return true;
        }
        return false;
    }

    private static boolean isTwoArgumentOperator(char character) {
        char[] allowedCharacters = {'=', '<', '>', '+' , '-', '*', '/', '%', '^'};
        for (int i = 0; i < 9; i++) {
            if (character == allowedCharacters[i]) return true;
        }
        return false;
    }

}

class StackChar {
    int size;
    char[] array;
    int lastElement;

    StackChar(int sizeOfStack) {
        this.size = sizeOfStack;
        this.array = new char[sizeOfStack];
        this.lastElement = 0;
    }

    public void push(char value) {
        this.array[this.lastElement] = value;
        this.lastElement++;
    }

    public char pop() {
        if (this.lastElement > 0 ) {
            char result = this.array[this.lastElement - 1];
            this.lastElement--;
            return result;
        }
        return '0';
    }

    public char getLastElement() {
        if (this.lastElement > 0 )
            return this.array[this.lastElement - 1];
        return '0';
    }

    public void print () {
        for (int i = this.lastElement - 1; i >= 0; i--) {
            System.out.print(this.array[i]);
        }

    }

}

class StackInt {
    int size;
    int[] array;
    int lastElement;

    StackInt(int sizeOfStack) {
        this.size = sizeOfStack;
        this.array = new int[sizeOfStack];
        this.lastElement = 0;
    }

    public void push(int value) {
        this.array[this.lastElement] = value;
        this.lastElement++;
    }

    public int pop() {
        if (this.lastElement > 0 ) {
            int result = this.array[this.lastElement - 1];
            this.lastElement--;
            return result;
        }
        return 0;
    }

    public int getLastElement() {
        if (this.lastElement > 0 )
            return this.array[this.lastElement - 1];
        return 0;
    }
}

class StackString {
    int size;
    String[] array;
    int lastElement;

    StackString(int sizeOfStack) {
        this.size = sizeOfStack;
        this.array = new String[sizeOfStack];
        this.lastElement = 0;
    }

    public void push(String value) {
        this.array[this.lastElement] = value;
        this.lastElement++;
    }

    public void push(char value) {
        this.array[this.lastElement] = Character.toString(value);
        this.lastElement++;
    }

    public String pop() {
        if (this.lastElement > 0 ) {
            String result = this.array[this.lastElement - 1];
            this.lastElement--;
            return result;
        }
        return "0";
    }
}


/*
INPUT:
51
ONP: xabc**=
ONP: ab+a~a-+
INF: a+b+(~a-a)
INF: x=~~a+b*c
INF: t=~a<x<~b
INF: ( a,+ b)/..[c3
ONP: ( a,b,.).c;-,*
ONP: abc++def++g+++
INF: x=a=b=c
ONP: xabc===
INF: a+b*(c^d-e)^(f+g*h)-i
ONP: abcd^e-fgh*+^*+i-
INF: a~+b
ONP: +a+b
INF: a~~
ONP: a~~
INF: a+b~
INF: ()a+b
INF: (a+b)+()
INF: ~()a
INF: (a-b)*c/d^e)
INF: (a-b)*c~/~(d^e)
INF: ((a-b)*c/d^e
INF: (a-b)(*c/d^e
INF: (a)-b)*c/d^e
INF: )(a-b)*c/d^e
INF: )+(a-b)*c/d^e
INF: (a-b)*c/d^e(
INF: (a-b)*c/d^e+(
INF: a+@/&-d
ONP: abc-+de^/
ONP: -abc-+de^/
ONP: a
INF: a
INF: a*b+c*d+d*e+f*g
ONP: ab*cd*+de*+fg*+
ONP: abcd+++
ONP: ab+c+d+
INF: a+b+c+d
INF: a+(b+(c+d))
INF: a^b^c^d
INF: ((a^b)^c)^d
ONP: ab*cd**
ONP: ab/c*
ONP: ab+cd++
INF: x=a^b^c
INF: (((((a) + b))))
INF: a+b=b-d
ONP: abc-+de-fg-h+/*
 */
/*
OUTPUT:
INF: x=a*(b*c)
INF: a+b+(~a-a)
ONP: ab+a~a-+
ONP: xa~~bc*+=
ONP: ta~x<b~<=
ONP: ab+c/
INF: a*(b-c)
INF: error
ONP: xabc===
INF: x=a=b=c
ONP: abcd^e-fgh*+^*+i-
INF: a+b*(c^d-e)^(f+g*h)-i
ONP: error
INF: error
ONP: error
INF: ~~a
ONP: error
ONP: error
ONP: error
ONP: error
ONP: error
ONP: error
ONP: error
ONP: error
ONP: error
ONP: error
ONP: error
ONP: error
ONP: error
ONP: error
INF: (a+(b-c))/d^e
INF: error
INF: a
ONP: a
ONP: ab*cd*+de*+fg*+
INF: a*b+c*d+d*e+f*g
INF: a+(b+(c+d))
INF: a+b+c+d
ONP: ab+c+d+
ONP: abcd+++
ONP: abcd^^^
ONP: ab^c^d^
INF: a*b*(c*d)
INF: a/b*c
INF: a+b+(c+d)
ONP: xabc^^=
ONP: ab+
ONP: error
INF: (a+(b-c))*((d-e)/(f-g+h))
 */


