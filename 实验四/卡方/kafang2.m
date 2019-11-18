function [ S,P_value ] = kafang2( image,rate )
% 函数功能：先对图像以嵌入率为rate进行顺序LSB嵌入，然后进行卡方隐写分析
% 输入参数：input是原始图像，rate是嵌入率，取值在[0,1]
% 输出参数：S存放卡方统计值，P保存对应的p值，即观察值与估计值相似程度的概率
% 调用例子：[ S,P_value ] = kafang( 'livingroom.tif',0.5 )
%读一幅图像


cover=imread(image);
%cover=cover(:,:,1);
ste_cover=double(cover); 
[m,n]=size(ste_cover); 

%依据rate计算秘密信息位的长度，并生成秘密信息msg
msglen=floor(m*n*rate);
msg= rand(1,msglen);  %这里可以直接用randint，如果机器上有的话
for i=1:msglen
    if msg(i)>=0.5
        msg(i)=1;
    else
        msg(i)=0;
    end
end
 
%使用lsb隐写算法嵌入秘密信息
p=1;
for f2=1:n
    for f1=1:m      
       if p>=msglen
         break;
       end
       ste_cover(f1,f2)=ste_cover(f1,f2)-mod(ste_cover(f1,f2),2)+msg(1,p);
       p=p+1;
    end
    if p==msglen
        break;
    end
end 

 %将ste_cover转换为uint8类型，使得imhist可以正常工作
 ste_cover=uint8( ste_cover);
 
 S=[];
 P_value=[];
 
 %将图像按5%的分割，一共分成20份
 interval=n/20;
 for j=0:19
    h=imhist(ste_cover(:,floor(j* interval)+1:floor((j+1)* interval)));
    h_length=size(h);
    p_num=floor(h_length/2);   
    Spov=0; %记录卡方统计量
    K=0;
    for i=1:p_num
        if(h(2*i-1)+h(2*i))~=0
            Spov=Spov+(h(2*i-1)-h(2*i))^2/(2*(h(2*i-1)+h(2*i))); 
            K=K+1;
        end
    end
    %Spov为卡方统计量，K-1为自由度
    P=1-chi2cdf(Spov,K-1);   
    
    if j~=0
     %  Spov=Spov+S(j); %若不注释则为累计卡方统计量 
    end
    
    S=[S Spov];
    P_value=[ P_value P];
 end

%显示变化曲线，x_label是横坐标，代表分析样本占整幅图像的百分比
x_label=5:5:100;
figure,
subplot(211),plot(x_label,S,'LineWidth',2),title('X^2统计');
subplot(212),plot(x_label,P_value,'LineWidth',2),title('p值');