N=256;%
f=428856000:48000:441144000;
t=pi/4:pi/(2*N):3*pi/4;
A=80*sin(t);

plot(t,A);

    fid = fopen ('1.txt', 'w');
    fprintf(fid, '\r\n\r');
    for i = 1:(N+1)       
       fprintf(fid, '%d', f(i));
       fprintf(fid, ';');
       fprintf(fid, '%d', floor(A(i)));
       fprintf(fid, ';\r\n');
    end
 fprintf(fid, '\r\n\r');
 fclose(fid);
 
 N=N/2;
 
    fid = fopen ('2.txt', 'w');
    for i = 1:(N)       
     if ((i>12)&&(i<115))  
       fprintf(fid, '%d', floor(A(i)));
     elseif fprintf(fid, '%d', 0);
       end
       fprintf(fid, '\r\n');
    end
 fprintf(fid, '\r\n\r');
 fclose(fid);
 
     fid = fopen ('2_etalon.txt', 'w');
    for i = 1:(N)       
     if ((i>12)&&(i<115))  
       fprintf(fid, '%d', max(A));
     elseif fprintf(fid, '%d', 0);
       end
       fprintf(fid, '\r\n');
    end
 fprintf(fid, '\r\n\r');
 fclose(fid);