import random
import numpy as np

# Constants
ROW_COUNT = 6
COLUMN_COUNT = 7
PLAYER_PIECE = 1
AI_PIECE = 2
EMPTY = 0
WINDOW_LENGTH = 4

# Create a game board
def create_board():
    board = np.zeros((ROW_COUNT, COLUMN_COUNT), dtype=int)
    return board

# Drop piece in the board
def drop_piece(board, row, col, piece):
    board[row][col] = piece

# Check if column is valid
def is_valid_location(board, col):
    return board[ROW_COUNT - 1][col] == EMPTY

# Get the next open row in the column
def get_next_open_row(board, col):
    for r in range(ROW_COUNT):
        if board[r][col] == EMPTY:
            return r

# Print the board
def print_board(board):
    print(np.flip(board, 0))

# Check for a win and return the winning positions
def winning_move(board, piece):
    # Check horizontal locations for win
    for c in range(COLUMN_COUNT - 3):
        for r in range(ROW_COUNT):
            if board[r][c] == piece and board[r][c+1] == piece and board[r][c+2] == piece and board[r][c+3] == piece:
                return True, [(r, c), (r, c+1), (r, c+2), (r, c+3)]

    # Check vertical locations for win
    for c in range(COLUMN_COUNT):
        for r in range(ROW_COUNT - 3):
            if board[r][c] == piece and board[r+1][c] == piece and board[r+2][c] == piece and board[r+3][c] == piece:
                return True, [(r, c), (r+1, c), (r+2, c), (r+3, c)]

    # Check positively sloped diagonals
    for c in range(COLUMN_COUNT - 3):
        for r in range(ROW_COUNT - 3):
            if board[r][c] == piece and board[r+1][c+1] == piece and board[r+2][c+2] == piece and board[r+3][c+3] == piece:
                return True, [(r, c), (r+1, c+1), (r+2, c+2), (r+3, c+3)]

    # Check negatively sloped diagonals
    for c in range(COLUMN_COUNT - 3):
        for r in range(3, ROW_COUNT):
            if board[r][c] == piece and board[r-1][c+1] == piece and board[r-2][c+2] == piece and board[r-3][c+3] == piece:
                return True, [(r, c), (r-1, c+1), (r-2, c+2), (r-3, c+3)]

    return False, []

# Evaluate window for AI scoring
def evaluate_window(window, piece):
    score = 0
    opp_piece = PLAYER_PIECE if piece == AI_PIECE else AI_PIECE

    if window.count(piece) == 4:
        score += 100
    elif window.count(piece) == 3 and window.count(EMPTY) == 1:
        score += 5
    elif window.count(piece) == 2 and window.count(EMPTY) == 2:
        score += 2

    if window.count(opp_piece) == 3 and window.count(EMPTY) == 1:
        score -= 4

    return score

# Scoring the current board position
def score_position(board, piece):
    score = 0

    # Center column preference
    center_array = [int(i) for i in list(board[:, COLUMN_COUNT // 2])]
    center_count = center_array.count(piece)
    score += center_count * 3

    # Horizontal
    for r in range(ROW_COUNT):
        row_array = [int(i) for i in list(board[r, :])]
        for c in range(COLUMN_COUNT - 3):
            window = row_array[c:c+WINDOW_LENGTH]
            score += evaluate_window(window, piece)

    # Vertical
    for c in range(COLUMN_COUNT):
        col_array = [int(i) for i in list(board[:, c])]
        for r in range(ROW_COUNT - 3):
            window = col_array[r:r+WINDOW_LENGTH]
            score += evaluate_window(window, piece)

    # Positive diagonal
    for r in range(ROW_COUNT - 3):
        for c in range(COLUMN_COUNT - 3):
            window = [board[r+i][c+i] for i in range(WINDOW_LENGTH)]
            score += evaluate_window(window, piece)

    # Negative diagonal
    for r in range(ROW_COUNT - 3):
        for c in range(COLUMN_COUNT - 3):
            window = [board[r+3-i][c+i] for i in range(WINDOW_LENGTH)]
            score += evaluate_window(window, piece)

    return score

# Check if game is over (full board or win)
def is_terminal_node(board):
    return winning_move(board, PLAYER_PIECE)[0] or winning_move(board, AI_PIECE)[0] or len(get_valid_locations(board)) == 0

# Minimax algorithm with alpha-beta pruning
def minimax(board, depth, alpha, beta, maximizingPlayer):
    valid_locations = get_valid_locations(board)
    terminal = is_terminal_node(board)
    if depth == 0 or terminal:
        if terminal:
            if winning_move(board, AI_PIECE)[0]:
                return (None, 100000000000000)
            elif winning_move(board, PLAYER_PIECE)[0]:
                return (None, -10000000000000)
            else:  # Game is over, no more valid moves
                return (None, 0)
        else:  # Depth is zero
            return (None, score_position(board, AI_PIECE))
    if maximizingPlayer:
        value = -np.inf
        best_col = random.choice(valid_locations)
        for col in valid_locations:
            row = get_next_open_row(board, col)
            b_copy = board.copy()
            drop_piece(b_copy, row, col, AI_PIECE)
            new_score = minimax(b_copy, depth-1, alpha, beta, False)[1]
            if new_score > value:
                value = new_score
                best_col = col
            alpha = max(alpha, value)
            if alpha >= beta:
                break
        return best_col, value
    else:  # Minimizing player
        value = np.inf
        best_col = random.choice(valid_locations)
        for col in valid_locations:
            row = get_next_open_row(board, col)
            b_copy = board.copy()
            drop_piece(b_copy, row, col, PLAYER_PIECE)
            new_score = minimax(b_copy, depth-1, alpha, beta, True)[1]
            if new_score < value:
                value = new_score
                best_col = col
            beta = min(beta, value)
            if alpha >= beta:
                break
        return best_col, value

# Get valid columns for next move
def get_valid_locations(board):
    valid_locations = []
    for col in range(COLUMN_COUNT):
        if is_valid_location(board, col):
            valid_locations.append(col)
    return valid_locations

# Main game loop
def play_game():
    board = create_board()
    game_over = False
    turn = 0

    print_board(board)

    while not game_over:
        if turn == 0:
            # Player's turn
            col = int(input("Player 1 Make your Selection (0-6): "))

            if is_valid_location(board, col):
                row = get_next_open_row(board, col)
                drop_piece(board, row, col, PLAYER_PIECE)

                is_win, winning_positions = winning_move(board, PLAYER_PIECE)
                if is_win:
                    print("PLAYER 1 WINS!")
                    print("Winning positions:", winning_positions)
                    game_over = True

        else:
            # AI's turn
            print("AI is thinking...")
            col, minimax_score = minimax(board, 5, -np.inf, np.inf, True)

            if is_valid_location(board, col):
                row = get_next_open_row(board, col)
                drop_piece(board, row, col, AI_PIECE)
                print(f"AI played column {col}")

                is_win, winning_positions = winning_move(board, AI_PIECE)
                if is_win:
                    print("AI WINS!")
                    print("Winning positions:", winning_positions)
                    game_over = True

        print_board(board)
        turn += 1
        turn = turn % 2

if __name__ == "__main__":
    play_game()
