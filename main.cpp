//
//  main.cpp
//  chessplus
//
//  Created by Mihnea Buzoiu on 6/5/23.
//

#include <iostream>
#include <array>
#include <vector>
#include <set>

using namespace std;

// code uses x as first coordinate

const int H = 8;
const int W = 8;

enum PieceColor
{
    cnone,
    white,
    black
};

enum PieceKind
{
    knone,
    king,
    pawn,
    knight,
    rook,
    bishop,
    queen
};

struct Piece {
    PieceColor color;
    PieceKind kind;
    
    Piece() {
        this->color = cnone;
        this->kind = knone;
    }
};

typedef pair<int, int> Pos;

class Board{
    array<array<Piece, H>, W> board;
    
public:
    
    void init() {
//        for (auto& column : board){
//            column[0].color = white;
//            column[0].kind = pawn;
//        }

        for (auto& column : board){
            column[7].color = black;
            column[7].kind = pawn;
        }
    }
    
    void print_valid_moves(const set<Pos> &moves){
        for (int i=0; i<W; i++){
            for (int j=0; j<H; j++)
                cout << moves.contains({i, j});
            cout << endl;
        }
        cout << endl;
    }
    
    bool check_diagonals(Pos from, Pos to){
        set<Pos> moves;
        
        for (int i=from.first+1, j=from.second+1; i<W && j<H; i++, j++){
            if (board[i][j].color == board[from.first][from.second].color)
                break;
            moves.insert({i, j});
            if (board[i][j].kind != knone)
                break;
        }
        
        for (int i=from.first+1, j=from.second-1; i<W && j>=0; i++, j--){
            if (board[i][j].color == board[from.first][from.second].color)
                break;
            moves.insert({i, j});
            if (board[i][j].kind != knone)
                break;
        }
        
        for (int i=from.first-1, j=from.second+1; i>=0 && j<H; i--, j++){
            if (board[i][j].color == board[from.first][from.second].color)
                break;
            moves.insert({i, j});
            if (board[i][j].kind != knone)
                break;
        }
        
        for (int i=from.first-1, j=from.second-1; i>=0 && j>=0; i--, j--){
            if (board[i][j].color == board[from.first][from.second].color)
                break;
            moves.insert({i, j});
            if (board[i][j].kind != knone)
                break;
        }
        
        // print moves
        print_valid_moves(moves);
        
        if (moves.contains(to)) return true;
        else return false;
    }
    
    bool check_lines(Pos from, Pos to){
        set<Pos> moves;
        
        for (int i=from.first+1, j=from.second; i<W; i++){
            if (board[i][j].color == board[from.first][from.second].color)
                break;
            moves.insert({i, j});
            if (board[i][j].kind != knone)
                break;
        }
        
        for (int i=from.first, j=from.second+1; j<H; j++){
            if (board[i][j].color == board[from.first][from.second].color)
                break;
            moves.insert({i, j});
            if (board[i][j].kind != knone)
                break;
        }
        
        for (int i=from.first-1, j=from.second; i>=0; i--){
            if (board[i][j].color == board[from.first][from.second].color)
                break;
            moves.insert({i, j});
            if (board[i][j].kind != knone)
                break;
        }
        
        for (int i=from.first, j=from.second-1; j>=0; j--){
            if (board[i][j].color == board[from.first][from.second].color)
                break;
            moves.insert({i, j});
            if (board[i][j].kind != knone)
                break;
        }
        
        // print moves
        print_valid_moves(moves);
        
        if (moves.contains(to)) return true;
        else return false;
    }
    
    bool valid_move(Pos from, Pos to, PieceKind kind, PieceColor color) {
        
        // no out of bound moves
        if (from.first > W || from.first < 0 || from.second > H || from.second < 0 ||
            to.first > W || to.first < 0 || to.second > H || to.second < 0)
            return false;
        
        // [[[add verification for obstacle]]]
        
        // same color
        if (color != board[from.first][from.second].color)
            return false;
        
        // piece verifications
        switch(kind)
        {
            case knone: return false;
            case king: return false;
            case pawn: return false;
            case knight: return false;
            case bishop: return check_diagonals(from, to);
            case rook: return check_lines(from, to);
            case queen: return (check_diagonals(from, to) || check_lines(from, to));
        }
        
        return true;
    }
    
    bool hypothetical(Pos from, Pos to, PieceKind kind, PieceColor color){
        board[2][4].color = white;
        board[2][4].kind = bishop;
        return valid_move(from, to, kind, color);
    }
    
    void print() {
        for (auto column : board)
        {
            for (auto place : column)
                cout << place.kind;
            cout << endl;
        }
        cout << endl;
    }
};

int main(int argc, const char * argv[]) {
    
    Board board;
    
    board.init();
    board.print();
    
    cout << board.hypothetical({2,4}, {7,7}, bishop, white);
    
    return 0;
}
