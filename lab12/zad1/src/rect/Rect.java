package rect;

/**
 * Created by Michał on 08.01.2018.
 */
public class Rect  implements Comparable<Rect> {

        private final int posX;
        private final int posY;
        private final int height;
        private final int width;
        private final int angle;

        private Rect(int posX, int posY, int height, int width, int angle) {
            this.posX = posX;
            this.posY = posY;
            this.height = height;
            this.width = width;
            this.angle = angle;
        }

        public static Rect getInstance(int posX, int posY, int height,
                                            int width, int angle) {
            return new Rect(posX, posY, height, width, angle);
        }

        public Rect changeAll(Rect rectangle) {

            return new Rect(this.posX + rectangle.posX, this.posY
                    + rectangle.posY, this.height + rectangle.height, this.width
                    + rectangle.width, this.angle + rectangle.angle);

        }

        public Rect changePosX(int arg) {

            return new Rect(arg, posY, height, width, angle);

        }

        public Rect changePosY(int arg) {

            return new Rect(posX, arg, height, width, angle);

        }

        public Rect changeHeight(int arg) {

            return new Rect(posX, posY, arg, width, angle);

        }

        public Rect changeWidth(int arg) {
            return new Rect(posX, posY, height, arg, angle);

        }

        public Rect rotate90() {
            if (angle + 90 == 360)
                return new Rect(posX, posY, height, width, 0);
            else
                return new Rect(posX, posY, height, width, angle + 90);

        }


//

        @Override
        public String toString() {
            return "Rectangle [posX=" + posX + ", posY=" + posY + ", height="
                    + height + ", width=" + width + ", angle=" + angle + "]";
        }

        public int getPosX() {
            return posX;
        }

        public int getPosY() {
            return posY;
        }

        public int getHeight() {
            return height;
        }

        public int getWidth() {
            return width;
        }

        @Override
        public int compareTo(Rect arg) {
            if (this.width * this.height < arg.height * arg.width)
                return -1;
            else if (this.width * this.height == arg.height * arg.width)
                return 0;
            else
                return 1;
        }

        public int getAngle() {
            return angle;
        }

    }


