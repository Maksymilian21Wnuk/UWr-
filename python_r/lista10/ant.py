import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

BOUNDARIES = 100

BLACK = np.array([0,0,0])
WHITE = np.array([255, 255, 255])

class Direction:
    directions =  ["e", "s", "w", "n"] # east south west north

    def __init__(self):
        self.cur = 0
        self.directions = ["e", "s", "w", "n"]

    def rotate_left(self):
        if self.cur == 0:
            self.cur = 3
        else:
            self.cur -= 1

    def rotate_right(self):
        if self.cur == 3:
            self.cur = 0
        else:
            self.cur += 1
            
    def get_dir(self):
        return self.directions[self.cur]
    

class Ant:    
    def __init__(self, x, y, img):
        self.x = x
        self.y = y
        self.img = img
        self.dir = Direction()

    def check_boundaries(self):
        if self.x > BOUNDARIES or self.x < 0:
            return False
        if self.y > BOUNDARIES or self.y < 0:
            return False
        return True

    def set_walk_dir(self, cur_dir):
        if cur_dir == "e":
            self.x += 1
        elif cur_dir == "s":
            self.y += 1
        elif cur_dir == "w":
            self.x -= 1
        else:
            self.y -= 1

        return self.check_boundaries()
    
    def walk(self):
        cur_color = self.img[self.x][self.y]
        if  np.all(cur_color == WHITE):
            self.dir.rotate_right()
            self.img[self.x][self.y] = BLACK
            
        elif np.all(cur_color == BLACK):
            self.dir.rotate_left()
            self.img[self.x][self.y] = WHITE
            
        return self.set_walk_dir(self.dir.get_dir())
    
    

class AntGame:
    def __init__(self, x, y, img):
        self.ant = Ant(x, y, img)
        self.fig, self.ax = plt.subplots()
        self.img_plot = self.ax.imshow(img)
        self.ani = animation.FuncAnimation(self.fig, self.update, interval=1, blit=False)

    def start(self):
        plt.show()

    def update(self, frame):
        if self.ant.walk():
            self.img_plot.set_array(self.ant.img)
            return self.img_plot,

        self.ani.event_source.stop()
        return self.img_plot,
        


def main():
    img = np.zeros((BOUNDARIES, BOUNDARIES, 3), dtype= np.uint8)
    img = np.full_like(img, WHITE, dtype= np.uint8)

    AntGame(50,  50, img).start()
    AntGame(300, 120, img).start()



if __name__ == "__main__":
    main()