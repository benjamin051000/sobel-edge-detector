i = dlmread("output.txt");
i = uint8(i);
imwrite(i, "output.jpg")
