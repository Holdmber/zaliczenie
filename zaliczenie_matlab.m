%% Otwarcie polaczenia kanalu Matlaba -> Drukarka
% TYLKO RAZ
% s = serial('/dev/ttyUSB0'); s.BaudRate = 115200; fopen(s)

%% Proste jezdzenie w gore i w dol 100 razy
% while(100)
%     fprintf(s,'k1 500; k2 500; k3 500');
%     pause(2);
%     fprintf(s,'k1 -500; k2 -500; k3 -500');
%     pause(2);
% end
%% okregi
stare1=round(100*sin(0));
stare2=round(100*sin(-2.09));
stare3=round(100*sin(-4.19));
for t=0:0.1:628
    a=round(100*sin(t));
    b=round(100*sin(t-2.09));
    c=round(100*sin(t-4.19));
    fprintf(s,'k1 %d; k2 %d; k3 %d\n',[a-stare1 b-stare2 c-stare3]);
    while(s.BytesAvailable == 0)
        ;
    end
    while(s.BytesAvailable > 0)
        fscanf(s)
    end
    stare1=a;
    stare2=b;
    stare3=c;
%     fprintf(s,'k1 %d; k2 %d; k3 %d');
%     while(s.BytesAvailable == 0)
%         ;
%     end
%     while(s.BytesAvailable > 0)
%         fscanf(s)
%     end
%     
end
