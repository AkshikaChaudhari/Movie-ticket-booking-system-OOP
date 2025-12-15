#include <iostream>
#include <string>
using namespace std;

class Movie {
protected:
    string title;
    string showtime;
    int seat[5][5]; // 5x5 seat arrangement
public:
    Movie(string t, string st) {
        title = t;
        showtime = st;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++){
                seat[i][j] = 0;
            }
        }
    }

    virtual void showMovieInfo() {
        cout << "Movie: " << title << " - Show Time: " << showtime << endl;
    }

    void showSeats() {
        cout << "\nSeat Arrangement (0 = Available, 1 = Booked):\n";
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                cout << seat[i][j] << " ";
            }

            cout<<endl;
        }
    }

    bool bookSeat(int row, int col) {
        if (row >= 0 && row < 5 && col >= 0 && col < 5) {
            if (seat[row][col] == 0) {
                seat[row][col] = 1;
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }

    string getTitle() { 
        return title; 
    }
    string getShowTime() { 
        return showtime; 
    }
};

class ActionMovie : public Movie {
public:
    ActionMovie(string t, string st) : Movie(t, st) {}
    void showMovieInfo() { 
        cout << "[Action] Movie: " << title << " - Show Time: " << showtime << endl; 
    }
};

class ComedyMovie : public Movie {
public:
    ComedyMovie(string t, string st) : Movie(t, st) {}
    void showMovieInfo() { 
        cout << "[Comedy] Movie: " << title << " - Show Time: " << showtime << endl; 
    }
};

class DramaMovie : public Movie {
public:
    DramaMovie(string t, string st) : Movie(t, st) {}
    void showMovieInfo() { 
        cout << "[Drama] Movie: " << title << " - Show Time: " << showtime << endl; 
    }
};

int main() {
    DramaMovie m1("Drishyam", "5:45 PM");
    DramaMovie m2("Super 30", "6:30 PM");
    ActionMovie m3("Ra-One", "7:00 PM");
    ComedyMovie m4("Stree 2", "8:15 PM");
    ComedyMovie m5("3 Idiots", "9:00 PM");

    Movie* movies[5] = { &m1, &m2, &m3, &m4, &m5 };

    string userName;
    cout << "Enter your name: ";
    getline(cin, userName);

    cout << "\n===== Welcome " << userName << " to Movie Ticket Booking System =====\n";
    
    cout << "Available Movies:\n";
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". ";
        movies[i]->showMovieInfo();
    }

    int movieChoice;
    while (true) {
        cout << "\nEnter the number of the movie you want to watch (1-5): ";
        cin >> movieChoice;
        if (movieChoice >= 1 && movieChoice <= 5) break;
        cout << "Invalid choice. Try again.\n";
    }

    Movie* selectedMovie = movies[movieChoice - 1];
    cout << "\nYou selected: ";
    selectedMovie->showMovieInfo();

    int bookedSeats[5][5]; // store row and column of booked seats
    int count = 0;
    char another = 'y';
    cin.ignore(); // clear buffer before reading chars

    while (another == 'y' || another == 'Y') {
        selectedMovie->showSeats();
        int row, col;
        cout << "Enter seat row (0-4): ";
        cin >> row;
        cout << "Enter seat column (0-4): ";
        cin >> col;

        if (selectedMovie->bookSeat(row, col)) {
            bookedSeats[count][0] = row;
            bookedSeats[count][1] = col;
            count++;
            cout << "Seat booked successfully!\n";
        } else {
            cout << "Seat already booked or invalid. Try again.\n";
            continue;
        }

        cout << "\nDo you want to book another seat? (y/n): ";
        cin >> another;
        cin.ignore();
    }

    // Print booking summary
    cout << "\n===== Booking Summary =====\n";
    cout << "Customer Name: " << userName << endl;
    cout << "Movie Number: " << movieChoice << endl;
    cout << "Movie Name: " << selectedMovie->getTitle() << endl;
    cout << "Show Time: " << selectedMovie->getShowTime() << endl;
    cout << "Seats Booked: ";
    for (int i = 0; i < count; i++) {
        cout << "(" << bookedSeats[i][0] << "," << bookedSeats[i][1] << ") ";
    }
    cout << "\nUpdated Seat Arrangement:\n";
    selectedMovie->showSeats();

    cout << "\n===== Thank You for Booking! Enjoy your movie =====\n";

    return 0;
}






