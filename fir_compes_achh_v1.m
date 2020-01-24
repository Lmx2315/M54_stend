pkg load signal;
close all;
clear all;

N=128;
B=16;
t=1:N;

spectr_r=load('2.txt')';
spectr_e=load('2_etalon.txt')';

s_r=10.^(spectr_r/20);
s_e=10.^(spectr_e/20);

s_o=s_e./s_r;

s_o=circshift(s_o,N/2,2);%%сдвигаем одномерный вектор по кольцу

##figure(1);
##plot(t,s_o);
##figure(2);
##plot(t,spectr_e);
##figure(3);
##plot (t,s_o);

  pfir = fftshift(ifft(s_o));
% pfir = ifft(s_o);
%figure(4);
%plot(t,20*log10(abs(fft(pfir))));
%freqz(pfir);

##figure(5);
##plot(t,pfir);

w_k     = flattopwin (N);
w_k=w_k';

pfir_win=pfir.*w_k;%накладываем окно чтобы сгладить 

h_i=real(pfir_win);
h_q=imag(pfir_win);

##H_i      = h_i/max(h_i);              %% Floating point coefficients
##H_i_norm = round(h_i*power(2,B-1)-1); %% Fixed point coefficients
##
##H_q      = h_q/max(h_q);              %% Floating point coefficients
##H_q_norm = round(h_q*power(2,B-1)-1); %% Fixed point coefficients

H_i      = h_i/max(h_i);              %% Floating point coefficients
H_i_norm = (h_i*power(2,B-1)-1); %% Fixed point coefficients

H_q      = h_q/max(h_q);              %% Floating point coefficients
H_q_norm = (h_q*power(2,B-1)-1); %% Fixed point coefficients

pfir_win=H_i_norm.+i.*H_q_norm;

figure(4);
plot(t,20*log10(abs(fft(pfir_win))));

figure(6);
plot(t,H_i_norm);

  fid = fopen ('fir_code_csharp_m54.dat', 'w');
    fprintf(fid, 'double [] H_q =  {');
    for i = 1:(N)       
       fprintf(fid, '%d', H_i_norm(i));
       if (i<(N))       fprintf(fid, ','); 
        elseif          fprintf(fid, '};'); 
      end
     end
     fprintf(fid, '\r\r\n\n');

    fprintf(fid, 'double [] H_i =  {');
    for i = 1:(N)       
       fprintf(fid, '%d', H_q_norm(i));
       if (i<(N))       fprintf(fid, ','); 
        elseif          fprintf(fid, '};'); 
     end
      end     
 fprintf(fid, '\r\n\n');
 
 fprintf(fid, '\r\r\n\n');

    fprintf(fid, 'double [] F_w =  {');
    for i = 1:(N)       
       fprintf(fid, '%d', w_k(i));
       if (i<(N))       fprintf(fid, ','); 
        elseif          fprintf(fid, '};'); 
     end
      end     
 fprintf(fid, '\r\n\n');  
 
 
    fprintf(fid, 'double [] k_ach_i =  {');
    for i = 1:(N)       
       fprintf(fid, '%d', s_o(i));
       if (i<(N))       fprintf(fid, ','); 
        elseif          fprintf(fid, '};'); 
      end
     end
     fprintf(fid, '\r\r\n\n'); 
 
 fclose(fid);
