// Krzysztof Wydrzynski - 4
import java.util.Scanner;

public class Source {
    public static Scanner in = new Scanner(System.in);


    public static void insertLast(Train train, Carriage carriage) {
        if (train.last.next == train.first) { // normalny
            carriage.prev = train.last;
            carriage.next = train.first;

            train.last.next = carriage;
            train.first.prev = carriage;

            train.last = carriage;
            return;
        }
        carriage.prev = train.last;
        carriage.next = train.first;

        train.last.prev = carriage;
        train.first.prev = carriage;

        train.last = carriage;
    }

    public static void insertLast(Train train, String carriageName) {
        Carriage carriage = new Carriage(carriageName);
        insertLast(train, carriage);
    }

    public static void insertFirst(Train train, Carriage carriage) {
        if (train.first.next.prev == train.first) { // normalny

            carriage.next = train.first.next;
            carriage.prev = train.first;

            train.first.next.prev = carriage;
            train.first.next = carriage;

            return;
        }

        carriage.prev = train.first.next;
        carriage.next = train.first;

        train.first.next.next = carriage;
        train.first.next = carriage;

    }

    public static void insertFirst(Train train, String carriageName) {
        Carriage carriage = new Carriage(carriageName);
        insertFirst(train, carriage);
    }

    public static void reverse(Train train) {
        Carriage carry = train.first.prev;

        train.first.prev = train.first.next;
        train.first.next = carry;

        train.last = train.first.prev;
    }

    public static Carriage delLast(Train train) {
        if (train.first.next == train.last) { // 1 wagon
            train.first.next = null;
            train.first.prev = null;
            return train.last;
        } if (train.last.next == train.first) { // normalny
            Carriage element = train.last;

            if (element.prev.prev == element) { // jeszcze raz obrocony
                train.last = element.prev;
                train.first.prev = train.last;
                train.last.prev = train.first;

                return element;
            }

            train.last = element.prev; // normalny
            train.first.prev = train.last;
            train.last.next = train.first;

            return element;
        }

        Carriage element = train.last;

        if (element.next.next == element) { // jeszcze raz obrocony
            train.last = element.next;
            train.first.prev = train.last;
            train.last.next = train.first;

            return element;
        }

        train.last = element.next;
        train.first.prev = train.last;
        train.last.prev = train.first;

        return element;
    }

    public static Carriage delFirst(Train train) {
        if (train.first.next == train.last) { // 1 wagon
            train.first.next = null;
            train.first.prev = null;
            return train.last;
        } else if (train.first.next.prev == train.first) { // normalny
            Carriage element = train.first.next;

            if (element.next.next == element) { // jeszcze raz obrocony
                train.first.next = element.next;
                train.first.next.next = train.first;

                return element;
            }

            train.first.next = element.next;
            train.first.next.prev = train.first;

            return element;
        }

        Carriage element = train.first.next; // odwrocony

        if (element.prev.prev == element) { // jeszcze raz obrocony
            train.first.next = element.prev;
            train.first.next.prev = train.first;

            return element;
        }

        train.first.next = element.prev;
        train.first.next.next = train.first;

        return element;
    }


    public static void print(Train train) {

        boolean goForward = true;

        Carriage element = train.first;
        if (element.next.next == element) {
            goForward = false;
        }
        element = element.next;
        while (element != train.first) {
            System.out.print(element.name + " ");
            if (goForward) {
                if (element.next.prev != element) {
                    goForward = false;
                }
                element = element.next;
            } else {
                if (element.prev.next != element) {
                    goForward = true;
                }
                element = element.prev;
            }
        }

    }

    public static void main (String[] args) {
        int dataSetsNumber = in.nextInt();

        for (int i = 0; i < dataSetsNumber; i++) {
            int linesIn = in.nextInt();
            TrainList trainList = new TrainList();
            for (int j = 0; j < linesIn; j++) {
                String operation;
                operation = in.next();
                switch (operation) {
                    case "New": {
                        String trainName = in.next();
                        String carriageName = in.next();

                        if (trainList.find(trainName) != null) {
                            System.out.println("Train " + trainName + " already exists");
                            break;
                        }

                        trainList.add(trainName, carriageName);
                        break;
                    }
                    case "InsertFirst": {
                        String trainName = in.next();
                        String carriageName = in.next();
                        Train train = trainList.find(trainName);
                        if (train == null) {
                            System.out.println("Train " + trainName + " does not exist");
                            break;
                        }
                        insertFirst(train, carriageName);
                        break;
                    }
                    case "InsertLast": {
                        String trainName = in.next();
                        String carriageName = in.next();
                        Train train = trainList.find(trainName);
                        if (train == null) {
                            System.out.println("Train " + trainName + " does not exist");
                            break;
                        }
                        insertLast(train, carriageName);
                        break;
                    }
                    case "Display": {
                        String trainName = in.next();
                        Train train = trainList.find(trainName);
                        if (train == null) {
                            System.out.println("Train " + trainName + " does not exist");
                            break;
                        }
                        System.out.print(trainName + ": ");
                        print(train);
                        System.out.println();
                        break;
                    }
                    case "Trains": {
                        System.out.print("Trains: ");
                        if (trainList.top == null) {
                            System.out.println();
                            break;
                        }
                        trainList.print();
                        System.out.println();
                        break;
                    }
                    case "Reverse": {
                        String trainName = in.next();
                        Train train = trainList.find(trainName);
                        if (train == null) {
                            System.out.println("Train " + trainName + " does not exist");
                            break;
                        }
                        reverse(train);
                        break;
                    }
                    case "Union": {
                        String firstTrainName = in.next();
                        String secondTrainName = in.next();
                        Train firstTrain = trainList.find(firstTrainName);
                        Train secondTrain = trainList.find(secondTrainName);
                        if (firstTrain == null) {
                            System.out.println("Train " + firstTrainName + " does not exist");
                            break;
                        }
                        if (secondTrain == null) {
                            System.out.println("Train " + secondTrainName + " does not exist");
                            break;
                        }
                        trainList.union(firstTrain, secondTrain);
                        break;
                    }
                    case "DelFirst": {
                        String trainFromName = in.next();
                        String trainToName = in.next();
                        Train trainFrom = trainList.find(trainFromName);
                        if (trainFrom == null) {
                            System.out.println("Train " + trainFromName + " does not exist");
                            break;
                        }

                        if (trainList.find(trainToName) != null) {
                            System.out.println("Train " + trainToName + " already exists");
                            break;
                        }

                        Carriage firstCarriage = delFirst(trainFrom);
                        if (trainFrom.first.next == null) {
                            trainList.delete(trainFrom);
                        }

                        trainList.add(trainToName, firstCarriage.name);
                        break;
                    }
                    case "DelLast": {
                        String trainFromName = in.next();
                        String trainToName = in.next();
                        Train trainFrom = trainList.find(trainFromName);
                        if (trainFrom == null) {
                            System.out.println("Train " + trainFromName + " does not exist");
                            break;
                        }

                        if (trainList.find(trainToName) != null) {
                            System.out.println("Train " + trainToName + " already exists");
                            break;
                        }

                        Carriage lastCarriage = delLast(trainFrom);

                        if (trainFrom.first.next == null) {
                            trainList.delete(trainFrom);
                        }

                        trainList.add(trainToName, lastCarriage.name);
                        break;
                    }
                }
            }
        }
    }
}

class Carriage {
    public Carriage next;
    public Carriage prev;
    public String name;

    public Carriage(String linkName) {
        this.name = linkName;
    }
}



class Train {
    public Train next;
    public String name;
    public Carriage first;
    public Carriage last;

    public Train(String trainName, String carriageName) {
        this.name = trainName;
        this.first = new Carriage("#");
        Carriage firstCarriage = new Carriage(carriageName);
        this.first.next = firstCarriage;
        this.first.prev = firstCarriage;
        firstCarriage.next = this.first;
        firstCarriage.prev = this.first;
        this.last = firstCarriage;
        this.next = null;
    }
}

class TrainList {
    public Train top;

    public TrainList() {
        this.top = null;
    }

    public void add (Train train) {
        train.next = this.top;
        this.top = train;
    }

    public void add (String trainName, String carriageName) {
        if (find(trainName) != null) {
            System.out.println("Train " + trainName + " already exists");
            return;
        }
        Train train = new Train(trainName, carriageName);
        this.add(train);
    }

    public Train find (String trainName) {
        Train element = top;
        while (element != null) {
            if (element.name.equals(trainName)) {
                return element;
            }
            element = element.next;
        }
        return null;
    }

    public boolean find (Train train) {
        Train element = top;
        while (element != null && train != element) {
            element = element.next;
        }
        if (element == top) return false;
        return true;
    }

    public void print() {
        Train element = top;
        while (element != null) {
            System.out.print(element.name + " ");
            element = element.next;
        }
    }

    public void delete (Train train) {
        if (train == top) {
            top = train.next;
            return;
        }

        Train element = top;
        while (element != null && element.next != train) {
            element = element.next;
        }

        if (element == null) return;

        element.next = element.next.next;
    }

    public void union (Train train1, Train train2) {

        boolean train1IsReversed = true;
        boolean train2IsReversedEnd = true;
        boolean train2IsReversedStart = true;
        if (train2.first.next.prev == train2.first) train2IsReversedStart = false;
        if (train1.last.next == train1.first) train1IsReversed = false;
        if (train2.last.next == train2.first) train2IsReversedEnd = false;

        if (train1.first.next == train1.last) {
            if (train2.first.next == train2.last) {
                Source.insertLast(train1, train2.first.next);
                delete(train2);
                return;
            }
            if (train2IsReversedStart) {
                train1.last.next = train2.first.next;
                train2.first.next.next = train1.last;
            } else {
                train1.last.next = train2.first.next;
                train2.first.next.prev = train1.last;
            }

            if (train2IsReversedEnd) {
                train1.first.prev = train2.last;
                train2.last.prev = train1.first;
            } else {
                train1.first.prev = train2.last;
                train2.last.next = train1.first;
            }
                train1.last = train2.last;
                delete(train2);
                return;
        }
        if (train2.first.next == train2.last) {
            Source.insertLast(train1, train2.first.next);
            delete(train2);
            return;
        }




        if (train1IsReversed && train2IsReversedEnd) { // oba obrocone
            if (train2IsReversedStart) {
                train1.last.prev = train2.first.next;
                train2.first.next.next = train1.last;
            } else {
                train1.last.prev = train2.first.next;
                train2.first.next.prev = train1.last;
            }
            train1.first.prev = train2.last;
            train2.last.prev = train1.first;

            train1.last = train2.last;
            delete(train2);
            return;
        } if (train1IsReversed && !train2IsReversedEnd) { // pierwszy obrocny, drugi normalnie
            if (train2IsReversedStart) {
                train1.last.prev = train2.first.next;
                train2.first.next.next = train1.last;
            } else {
                train1.last.prev = train2.first.next;
                train2.first.next.prev = train1.last;
            }

            train1.first.prev = train2.last;
            train2.last.next = train1.first;

            train1.last = train2.last;

            delete(train2);
            return;
        } if (!train1IsReversed && train2IsReversedEnd) { // pierwszy normalnie, drugi obrocony
            if (train2IsReversedStart) {
                train1.last.next = train2.first.next;
                train2.first.next.next = train1.last;
            } else {
                train1.last.next = train2.first.next;
                train2.first.next.prev = train1.last;
            }
            train1.first.prev = train2.last;
            train2.last.prev = train1.first;

            train1.last = train2.last;

            delete(train2);
            return;
        }

        if (train2IsReversedStart) {
            train1.last.next = train2.first.next;
            train2.first.next.next = train1.last;
        } else {
            train1.last.next = train2.first.next;
            train2.first.next.prev = train1.last;
        }

        train1.first.prev = train2.last; // oba normalnie
        train2.last.next = train1.first;

        train1.last = train2.last;
        delete(train2);
        }
    }
/*
1
43
New A A2
New B A5
New C A8
New D A10
New E A11
New F A14
New G A16
InsertLast A A3
InsertFirst A A1
InsertLast B A6
InsertFirst B A4
InsertLast C A7
InsertFirst C A9
InsertLast E A12
InsertLast E A13
InsertLast D A12
InsertLast D A11
InsertLast G A15
InsertFirst G A17
Union E F
Reverse G
Union E G
Display E
Union A B
Display A
Reverse C
Union A C
Display A
Trains
Display D
DelLast D H
Union H D
DelLast H D
Union D H
Display D
Reverse D
Union A D
Display A
DelFirst E B
DelFirst E C
Union A E
Display A
Trains




E: A11 A12 A13 A14 A15 A16 A17
A: A1 A2 A3 A4 A5 A6
A: A1 A2 A3 A4 A5 A6 A7 A8 A9
Trains: E D A
D: A10 A12 A11
D: A12 A11 A10
A: A1 A2 A3 A4 A5 A6 A7 A8 A9 A10 A11 A12
A: A1 A2 A3 A4 A5 A6 A7 A8 A9 A10 A11 A12 A13 A14 A15 A16 A17
Trains: C B A

 */
