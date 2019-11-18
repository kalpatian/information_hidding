function result=binaryextract(stegocover,goalfile,key,R0,R1,lumda,count)
stegoimage=imread(stegocover);
stegoimage=round(double(stegoimage)/255);
%确定图像块的首地址
[m,n]=size(stegoimage);
m=floor(m/10);  %向负无穷大取整
n=floor(n/10);
temp=zeros([m,n]);
[row,col]=hashreplacement(temp,m*n,m,key,n);  %将m，n也作为密钥简化输入
%将块的坐标转换为块首像素地址
for i=1:m*n
    if row(i)~=1
        row(i)=(row(i)-1)*10+1;
    end
    if col(i)~=1
        col(i)=(col(i)-1)*10+1;
    end
end
%准备提取并回写信息
frr=fopen(goalfile,'a');
%按隐藏顺序分析图像块
quan=1;
result=zeros([count 1]);
for i=1:m*n
    %计算这一块的p1bi
    p1bi=computep1bi(row(i),col(i),stegoimage);
    if p1bi<R1+3*lumda && p1bi>50
        fwrite(frr,1,'ubit1');
        result(quan,1)=1;
        quan=quan+1;
    elseif p1bi>R0-3*lumda && p1bi<50
        fwrite(frr,0,'ubit1');
        result(quan,1)=0;
        quan=quan+1;
    else
        quan=quan;
    end
    if quan==count+1
        break;
    end
end
disp(['已经正确处理',num2str(quan-1),'bits的消息']);
fclose(frr);