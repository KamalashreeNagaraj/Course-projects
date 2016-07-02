%read image
im = imread('F:\College\PROJECTS\Multimedia Computing\trial1.png');

%change pixel values to 255, if less than 100, or into 0, if greater than 100
%converts grey-scale image to binary image
bw = im < 100;

%find centroids of objects in the image
%objects are braille dots, white in colour
s = regionprops(bw,'centroid');

%concatenate centroid values 
centroids = cat(1, s.Centroid);

%--------------------------------------------------------
%to display the image and plot the centroids on the image
imshow(bw)
hold on
plot(centroids(:,1),centroids(:,2), 'b*')
hold off
%--------------------------------------------------------

%--------------------------------------------------------
%centroids matrix contain co-ordinates of centroids
%fetch individual column in centroids matrix into a vector
%x-coordinates to column1
column = centroids(:,1);
%y-coordinates to row
row = centroids(:,2);
%sort the coordinate arrays
column = sort(column,1);
row = sort(row,1);
%find unique coordinates in the arrays
column = unique(column);
row = unique(row);
%dimension of row and column
columnsize = size(column);
rowsize = size(row);
%apply floor function to the array values
%estimate the coordinates to real positive integers
for x=1:columnsize
    column(x) = floor(column(x));
end
for x=1:rowsize
    row(x) = floor(row(x));
end
%--------------------------------------------------------

%--------------------------------------------------------
%find unique coordinates after estimation
column = unique(column);
row = unique(row);
%dimension of the arrays after finding unique values
columnsize = size(column);
rowsize = size(row);
%--------------------------------------------------------

%--------------------------------------------------------
%Map possible Braille code to corresponding intermediate English characters
keyBasic =   {' ','7', '74', '78', '785', '75','784', '7845', '745','84','845','71','741','781','7851','751','7841','78451','7451','841','8451', '712', '7412', '8452', '7812', '78512', '7512','82' ,'72', '8','51','451','852','7852','521','42','87412','5','742','851','12','2','4512','7452','45','41','1','4','452','81','412','8512', '52'};
valueBasic = {' ','a', 'b', 'c', 'd', 'e', 'f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','.','*' ,'`','9','6','_','?','0','5','&','"', '<','>','-',',','7','|','3','2','''', '1', '4', '/','8','#',';'};
mapObj = containers.Map(keyBasic,valueBasic);
%--------------------------------------------------------

%--------------------------------------------------------
%loop through the image for each character
%each character is a cell of six objects 
%in the order column first, row next
%mapped in the order 7-8-4-5-1-2
%append value to a string if the object exists at the centroid
%centroids are combination of 'x' and 'y' coordinates
str1 = '';
for x=1:3:rowsize
    for y=1:2:columnsize
        s = '';
        if bw(row(x),column(y)) == 1
            s = [s '7'];
        end
        if bw(row(x),column(y+1)) == 1
            s = [s '8'];
        end
        if bw(row(x+1),column(y)) == 1
            s = [s '4'];
        end
        if bw(row(x+1),column(y+1)) == 1
            s = [s '5'];
        end
        if bw(row(x+2),column(y)) == 1
            s = [s '1'];
        end
        if bw(row(x+2),column(y+1)) == 1
            s = [s '2'];
        end
        if strcmp(s,'') == 1
            s = [s ' '];
        end
        fprintf('%s',mapObj(s));
        str1 = [str1 mapObj(s)];
    end
    fprintf('\n');
    str1 = [str1 char(10)];
end
%fprintf('Intermediate English text:\n %s',str1);
%--------------------------------------------------------

%--------------------------------------------------------
%the intermediate english text obtained is contained in str1
%convert this intermediate text to conventional english text
%each intermediate english text character or combination of characters
%has a corresponding character in english text
%convert with the help of another hash table
keyFinal = {'.*' , '`','6','`a','_?','`s','.0','`5','`&','"9','"<','">','.-','"6',',-','"7','.<','.>','_<','_>','_|','3',',7','2','''','1','4','_/','`<','`>','8'};
valueFinal = {'`','~','!','@','#','$','%','^','&','*','(',')','_','+','-','=','[',']','{','}','|',':','"',';','''',',','.','/','<','>','?'};
mapObj2 = containers.Map(keyFinal,valueFinal);
keyNum = {'a','b','c','d','e','f','g','h','i','j'};
valueNum = {'1','2','3','4','5','6','7','8','9','0'};
mapObjNum = containers.Map(keyNum,valueNum);
strlist = double(str1);
i = 1;
finale = '';
listSize = size(strlist);
while i <= listSize(2)
    if (strlist(i)>96 && strlist(i)<123) || strlist(i) == 32 || strlist(i) == 10 || strlist(i) == 39
        finale = [finale char(strlist(i))];
        %disp(char(strlist(i));
        i = i + 1;
    elseif strlist(i) == 59
        i = i + 1;
    elseif strlist(i) == 45
        finale = [finale char(45)];
        i = i+1;
    elseif strlist(i) == 44 
        if strlist(i+1) == 44 
            i = i + 2;
            while strlist(i) ~= 32 && strlist(i) ~= 10  && ( strlist(i) ~= 44 && strlist(i+1) ~= 39) && (strlist(i)>96 && strlist(i)<123)
                strlist(i) = strlist(i) - 32;
                finale = [finale char(strlist(i))];
                %disp(char(strlist(i));
                i = i + 1; 
            end
            if strlist(i) == 32
                finale = [finale ' '];
               % disp(' ');
                i = i+1;
            elseif strlist(i) == 10
                finale = [finale char(10)];
            elseif strlist(i) == 44 && strlist(i+1) == 39
                i = i+2;
            end
        elseif( strlist(i+1) >= 97 && strlist(i+1) <= 122)
                strlist(i+1) = strlist(i+1) - 32;
                finale = [finale strlist(i+1)];
               % disp(char(strlist(i+1)));
                i = i+2;
        else 
                finale = [finale mapObj2([',' char(strlist(i+1))])];
               % disp(mapobj2([',' [char(strlist(i+1))]]));
                i = i+2;
        end
    elseif strlist(i) == 96 %`<_>
        finale = [finale mapObj2(['`' char(strlist(i+1))])];
       % disp(mapobj2(['`' [char(strlist(i+1))]]));
        i = i+2;
    elseif strlist(i) == 46 %.<_> 
        finale = [finale mapObj2(['.' char(strlist(i+1))])];
       % disp(mapobj2(['.' [char(strlist(i+1))]]));
        i = i+2;
    elseif strlist(i) == 34 %"<_>
        finale = [finale mapObj2(['"' char(strlist(i+1))])];
        i = i+2;
    elseif strlist(i) == 95 %_<_>
        finale = [finale mapObj2(['_' char(strlist(i+1))])];
        i = i+2;
    elseif strlist(i)>= 48 && strlist(i)<=57 %direct number such as 6 for !
        finale = [finale mapObj2(char(strlist(i)))];
        i = i + 1;
    elseif strlist(i) == 35 % # followed by alpha read next
        i = i + 1;
        while(strlist(i) ~= 32 || strlist(i) ~= 59) && (strlist(i)>96 && strlist(i)<107)  %space or semicolon check
            finale = [finale mapObjNum(char(strlist(i)))];
            i = i + 1;
        end
    end
    %if i == 264
     %   break;
    %end
end
fprintf('\n\nConventional English text : \n%s',finale);
%--------------------------------------------------------
