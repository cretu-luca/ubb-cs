import tkinter as tk
from tkinter import messagebox, font, Label, Button, Listbox
from src.services.services import Services


class GUI:
    def __init__(self):
        service = Services()
        self.__configure_human_board = HumanComputerBoardConfiguration(service)
        self.__battle_board = BattleBoard(service)


class BattleBoard:
    def __init__(self, services):
        self.__services = services
        self.__window = tk.Tk()
        self.__window.geometry("1200x800")
        self.__window.title("Planes")
        self.__background_image = tk.PhotoImage(file="planes.png")
        self.__background_label = tk.Label(self.__window, image=self.__background_image)
        self.__background_label.place(relwidth=1, relheight=1)

        self.__human_player_board_frame = tk.Frame(self.__window, bg='white')
        self.__human_player_board_frame.place(relx=0.3, rely=0.5, anchor='center')
        self.__human_player_buttons = []
        self.generate_board(self.__human_player_buttons, self.__human_player_board_frame)

        self.__computer_player_board_frame = tk.Frame(self.__window, bg='white')
        self.__computer_player_board_frame.place(relx=0.7, rely=0.5, anchor='center')
        self.__computer_player_buttons = []

        self.generate_board(self.__computer_player_buttons, self.__computer_player_board_frame)

        self.update_human_player_board((0, 0), "setup", setup='setup')
        self.__window.mainloop()

    def generate_board(self, buttons, frame):
        board_size = 10
        for j in range(1, board_size + 1):
            header_button = tk.Button(frame, text=str(j), font=('Helvetica', 8), width=4, height=2, state='disabled')
            header_button.grid(row=0, column=j)

        for i in range(1, board_size + 1):
            header_button = tk.Button(frame, text=chr(64 + i), font=('Helvetica', 8), width=4, height=2, state='disabled')
            header_button.grid(row=i, column=0)

        for i in range(board_size):
            row = []
            for j in range(board_size):
                button = tk.Button(frame, text='', font=('Helvetica', 8), width=4, height=2,
                                   command=lambda line=i, column=j: self.button_command(line, column), relief='ridge')
                button.grid(row=i+1, column=j+1)
                row.append(button)
            buttons.append(row)

    def update_human_player_board(self, attack_coordinates, hit_type, **kwargs):
        board_size = 10
        no_hit_point = 4
        hit_point = 5
        downed_point = 6
        available_plane_codes = [1, 2, 3]
        board_state = self.__services.get_human_player_board_state()

        for i in range(board_size):
            for j in range(board_size):
                if i != attack_coordinates[0] or j != attack_coordinates[1] and self.__human_player_buttons[i][j].cget('bg') not in ['red', 'lightblue']:
                    if board_state[i][j] in available_plane_codes and self.__human_player_buttons[i][j].cget('bg') not in ['green', 'red', 'lightblue']:
                        self.__human_player_buttons[i][j].config(text=str(int(board_state[i][j])), bg='green')
                    elif board_state[i][j] == no_hit_point:
                        self.__human_player_buttons[i][j].config(text='o', bg='lightblue')
                    elif board_state[i][j] in [hit_point, downed_point]:
                        self.__human_player_buttons[i][j].config(text='x', bg='red')

                    if board_state[i][j] == '0':
                        self.__human_player_buttons[i][j].config(text='o', bg='lightblue')

        if 'setup' not in kwargs:
            if hit_type == "miss" and self.__human_player_buttons[attack_coordinates[0]][attack_coordinates[1]].cget('bg') not in ['red', 'lightblue']:
                (self.__human_player_buttons[attack_coordinates[0]][attack_coordinates[1]].config
                 (text=str(int(board_state[attack_coordinates[0]][attack_coordinates[1]])), bg='lightblue'))
            elif hit_type == "hit" and self.__human_player_buttons[attack_coordinates[0]][attack_coordinates[1]].cget('bg') not in ['red', 'lightblue']:
                (self.__human_player_buttons[attack_coordinates[0]][attack_coordinates[1]].config(text='x', bg='red'))

    def update_computer_player_board(self, line, column, hit_type, **kwargs):
        board_size = 10
        no_hit_point = 4
        hit_point = 5
        downed_point = 6
        board_state = self.__services.get_computer_player_board_state()

        for i in range(board_size):
            for j in range(board_size):
                if i != line or j != column:
                    if board_state[i][j] == no_hit_point:
                        self.__computer_player_buttons[i][j].config(text='o', bg='lightblue')
                    elif board_state[i][j] in [hit_point, downed_point]:
                        self.__computer_player_buttons[i][j].config(text='x', bg='red')

        if 'setup' not in kwargs:
            if hit_type == "miss":
                (self.__computer_player_buttons[line][column].config
                 (text='o', bg='lightblue'))
            elif hit_type == "hit":
                (self.__computer_player_buttons[line][column].config
                 (text='x', bg='red'))

    def button_command(self, line, column):
        attack_outcome, planes_left = self.__services.handle_attack_by_human_service(line, column)
        if "No plane was hit!" in attack_outcome:
            self.update_computer_player_board(line, column, "miss")
        else:
            self.update_computer_player_board(line, column, "hit")

        if planes_left == 0:
            messagebox.showinfo("Game Over", "You won!")
            self.__window.destroy()

        attack_outcome, planes_left = self.__services.handle_attack_by_computer_service()
        attack_coordinates = (ord(attack_outcome[20]) - ord('A'), int(attack_outcome[24]) - 1)
        if "No plane was hit!" in attack_outcome:
            self.update_human_player_board(attack_coordinates, "miss")
        else:
            self.update_human_player_board(attack_coordinates, "hit")

        if planes_left == 0:
            messagebox.showinfo("Game Over", "The computer won!")
            self.__window.destroy()


class HumanComputerBoardConfiguration:
    def __init__(self, services):
        self.__services = services
        self.__window = tk.Tk()
        self.__window.geometry("1200x800")
        self.__window.title("Planes")
        self.__number_of_planes_known = 0
        self.__board_buttons = None
        self.listbox = None
        self.orientation_window = None

        self.__background_image = tk.PhotoImage(file="planes.png")
        self.__background_label = tk.Label(self.__window, image=self.__background_image)
        self.__background_label.place(relwidth=1, relheight=1)

        button_font = font.Font(family='Helvetica', size=16)

        self.__select_plane_coordinates_button = tk.Button(self.__window, text='Select plane coordinates',
                                 command=self.select_plane_coordinates_button_click, height=5, width=28,
                                                           font=button_font, relief='ridge')
        self.__generate_plane_coordinates_button = tk.Button(self.__window, text='Generate plane coordinates',
                                 command=self.generate_plane_coordinates_button_click, height=5, width=28,
                                                             font=button_font, relief='ridge')

        self.__select_plane_coordinates_button.place(relx=0.5, rely=0.45, anchor='center')
        self.__generate_plane_coordinates_button.place(relx=0.5, rely=0.65, anchor='center')
        self.__window.mainloop()

    def place_plane(self, line, column):
        self.orientation_window = tk.Toplevel(self.__window)
        self.orientation_window.title("Select Plane Orientation")
        self.orientation_window.geometry("300x300")
        self.orientation_window.transient(self.__window)
        self.orientation_window.grab_set()

        Label(self.orientation_window, text="Choose the orientation:").pack()
        self.listbox = Listbox(self.orientation_window)
        self.listbox.pack()

        orientations = ['Up', 'Down', 'Left', 'Right']
        for orientation in orientations:
            self.listbox.insert(tk.END, orientation)

        ok_button = Button(self.orientation_window, text="OK", command=self.confirm_orientation_and_update_board)
        ok_button.pack()

        self.selected_line = line
        self.selected_column = column

        self.__window.wait_window(self.orientation_window)

    def confirm_orientation_and_update_board(self):
        try:
            index = self.listbox.curselection()[0]
            orientation_selected = self.listbox.get(index).lower()[0]

            plane_coordinates = self.__services.get_plane_coordinates_service(
                (self.selected_line, self.selected_column), orientation_selected
            )

            if not self.__services.check_friendly_plane_collision(plane_coordinates):
                self.orientation_window.destroy()
                raise ValueError

            if not self.__services.check_coordinates_validity(plane_coordinates):
                self.orientation_window.destroy()
                raise ValueError

            self.__number_of_planes_known += 1
            for coordinate in plane_coordinates:
                self.__board_buttons[coordinate[0]+1][coordinate[1]+1].config(text=self.__number_of_planes_known)

            self.orientation_window.destroy()

            self.__services.configure_board_service(line=self.selected_line, column=self.selected_column,
                                                    orientation_selected=orientation_selected,
                                                    number_of_planes_known=self.__number_of_planes_known)

            if self.__number_of_planes_known == 3:
                self.close_configuration()

        except IndexError:
            messagebox.showerror("Selection Error", "Please select an orientation.")
        except ValueError:
            messagebox.showerror("Selection Error", "Invalid coordinates.")

    def close_configuration(self):
        if self.orientation_window and self.orientation_window.winfo_exists():
            self.orientation_window.destroy()
        self.__window.destroy()

    def select_plane_coordinates_button_click(self):
        board_size = 10
        board_frame1 = tk.Frame(self.__window, bg='white')
        board_frame1.place(relx=0.5, rely=0.5, anchor='center')
        self.__board_buttons = []

        for i in range(board_size + 1):
            row = []
            for j in range(board_size + 1):
                if i == 0:
                    if j == 0:
                        label = tk.Label(board_frame1, text='', font=('Helvetica', 8), width=4, height=2)
                        label.grid(row=i, column=j)
                    else:
                        label = tk.Label(board_frame1, text=str(j), font=('Helvetica', 8), width=4, height=2)
                        label.grid(row=i, column=j)
                    row.append(label)
                else:
                    if j == 0:
                        label = tk.Label(board_frame1, text=chr(64 + i), font=('Helvetica', 8), width=4, height=2)
                        label.grid(row=i, column=j)
                        row.append(label)
                    else:
                        button = tk.Button(board_frame1, text='', font=('Helvetica', 8), width=4, height=2,
                                           command=lambda line=i-1, column=j-1: self.place_plane(line, column), relief='ridge')
                        button.grid(row=i, column=j)
                        row.append(button)
            self.__board_buttons.append(row)

    def generate_plane_coordinates_button_click(self):
        self.__services.generate_board_service("human_player_board")
        self.__window.destroy()


if __name__ == "__main__":
    GUI = GUI()
