#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
int size=720*560;
int red[720*560],green[720*560],blue[720*560],trans[720*560];
int r[720*560/2],g[720*560/2],b[720*560/2],t[720*560/2];
int defred[720*560],defgreen[720*560],defblue[720*560],deftrans[720*560];
int defr[720*560/2],defg[720*560/2],defb[720*560/2],deft[720*560/2];
struct Image
{
   int red;
   int blue;
   int green;
   int trans;
};
struct Image a[720][560];
struct Image defa[720][560];
void defaultpixels();
void read();
void convert();
void compare();
void main()
{
    int tempr[size/2],tempg[size/2],tempb[size/2],tempt[size/2];
    defaultpixels();
    for(int p=0;p<2;p++)//in real world scenario it is an infinite loop
    {
        read();//read rgb and transparency values of image
        convert();//converting 2D matrix to 1D
        compare();//store difference in values of adjacent pixels
        //human detection
        int countr=0,countg=0,countb=0,countt=0;
        for(int i=0;i<size/2;i+=2)
        {
            int x=30;//for the required scenario the value of x is predicted to be 30
            if((r[i+1]-r[i])>x||(r[i+1]-r[i])<-x)
                countr++;
            if((g[i+1]-g[i])>x||(g[i+1]-g[i])<-x)
                countg++;
            if((b[i+1]-b[i])>x||(b[i+1]-b[i])<-x)
                countb++;
            if((t[i+1]-t[i])>x||(t[i+1]-t[i])<-x)
                countt++;
        }
        int y=100,z=120;
        /*the value of count if found within the input range y&z for the given scenario
        can be considered to be a human*/
        if((countr>y&&countr<z)||(countg>y&&countg<z)||(countb>y&&countb<z)||(countt>y&&countt<z))
        {
            printf("Human Detected\n");
            int c=0;
            for(int i=0;i<size/2;i++)
            {
                if((defr[i]-r[i])>-15 && (defr[i]-r[i])<15)
                    c++;
                if((defg[i]-g[i])>-15 && (defg[i]-g[i])<15)
                    c++;
                if((defb[i]-b[i])>-15 && (defb[i]-b[i])<15)
                    c++;
                if((deft[i]-t[i])>-15 && (deft[i]-t[i])<15)
                    c++;
            }
            if(c<=4*(size/2) && c>=3*(size/2))
            {
                printf("The human detected is the required target\n");
                printf("Now proceeding with tracking of human movements\n");
                if(p==0)
                {
                    for(int i=0;i<size/2;i++)
                    {
                        tempr[i]=r[i];
                        tempg[i]=g[i];
                        tempb[i]=b[i];
                        tempt[i]=t[i];
                    }
                    continue;
                }
                else
                {
                    int ct=0;
                    for(int i=0;i<size/2;i++)
                    {
                        if((tempr[i]-r[i])>=-25 && (tempr[i]-r[i])<=25)
                            ct++;
                        if((tempg[i]-g[i])>=-25 && (tempg[i]-g[i])<=25)
                            ct++;
                        if((tempb[i]-b[i])>=-25 && (tempb[i]-b[i])<=25)
                            ct++;
                        if((tempt[i]-t[i])>=-25 && (tempt[i]-t[i])<=25)
                            ct++;
                    }
                    if(ct<=4*(size/2) && ct>=2*(size/2))
                    {
                        printf("Target is moving\n");
                        printf("\a");
                    }
                    else
                        printf("Target is not moing\n");
                    for(int i=0;i<size/2;i++)
                    {
                        tempr[i]=r[i];
                        tempg[i]=g[i];
                        tempb[i]=b[i];
                        tempt[i]=t[i];
                    }
                }
            }
            else
                printf("Behaviour of human detected doesnt match the required target\n");
        }
        else
            printf("Human not detected\n");
    }
}
void read()
{
    srand(time(NULL));
    for(int i=0;i<720;i++)
       for(int j=0;j<560;j++)
       {
           a[i][j].red = rand() % 256;
           a[i][j].blue = rand() % 256;
           a[i][j].green = rand() % 256;
           a[i][j].trans = rand() % 256;
       }
}
void convert()
{
    int k=0;
    for(int i=0;i<720;i++)
       for(int j=0;j<560;j++)
       {
           red[k]=a[i][j].red;
           green[k]=a[i][j].green;
           blue[k]=a[i][j].blue;
           trans[k]=a[i][j].trans;
           k++;
       }
}
void compare()
{
    for(int i=0,j=0;i<size;i+=2,j++)
    {
        r[j] = red[i+1]-red[i];
        g[j] = green[i+1]-green[i];
        b[j] = blue[i+1]-blue[i];
        t[j] = trans[i+1]-trans[i];
    }
}
/*The input containing the already scanned image of the target is given as the
default input to compare with the currently obtained image of the given time interval.
In this required case,we take random values generated as our input containing the details
of the target human required to be locked,*/
#include <math.h>
void defaultpixels()
{
    srand(time(NULL));
    for(int i=0;i<720;i++)
       for(int j=0;j<560;j++)
       {
           defa[i][j].red = rand() % 511 - 255;
           defa[i][j].blue = rand() % 511 - 255;
           defa[i][j].green = rand() % 511 - 255;
           defa[i][j].trans = rand() % 511 - 255;
       }
    int k=0;
    for(int i=0;i<720;i++)
       for(int j=0;j<560;j++)
       {
           defred[k]=defa[i][j].red;
           defgreen[k]=defa[i][j].green;
           defblue[k]=defa[i][j].blue;
           deftrans[k]=defa[i][j].trans;
           k++;
       }
    for(int i=0,j=0;i<size;i+=2,j++)
    {
        defr[j] = defred[i+1]-defred[i];
        defg[j] = defgreen[i+1]-defgreen[i];
        defb[j] = defblue[i+1]-defblue[i];
        deft[j] = deftrans[i+1]-deftrans[i];
    }
}


/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>//used for interacting with the Operating system
#include <fcntl.h>
#include <termios.h>

// configuring the function for communicating with the serial port

int configure_serial_port(const char *port) {
    int fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        perror("Unable to open serial port");
        return -1;
    }

    struct termios options;
    tcgetattr(fd, &options);
    cfsetispeed(&options, B19600);  // Setting the baud rate to a higher value to run more frames per second
    cfsetospeed(&options, B19600);

    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    tcsetattr(fd, TCSANOW, &options);

    return fd;
}

// Function to send a command to the UHF radar module and read the response

void send_command(int fd, const char *command, char *response, int response_size) {
    write(fd, command, strlen(command));
    
    usleep(100);  // reducing the delay more for the data to be read to input more frames in a second
    read(fd, response, response_size);
}

int main() {
    const char *serial_port = "/dev/ttyUSB0";  // Replace with the appropriate serial port
    int fd = configure_serial_port(serial_port);

    if (fd == -1) {
        return 1;
    }

    char response[1024];
    
    // Example commands
    send_command(fd, "INITIATE_RADAR\n", response, sizeof(response));
    printf("Response: %s\n", response);

    send_command(fd, "GET_RADAR_DATA\n", response, sizeof(response));
    printf("Radar Data: %s\n", response);

    close(fd);

// adding  additional function to return the value of input instead of randomly generated values required for the program to run.
// finally returning the output obtained by the API and linking it with the above code to obtain close to produce 
    return 0;
}
*/
