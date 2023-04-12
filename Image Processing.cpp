#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

void B_Sort(int a[], int s) {
    for (int i = 0; i < s - 1; i++) {
        for (int j = 0; j < s - 2 - i; j++) {
            if (a[j] < a[j + 1]) {
                int T = a[j];
                a[j] = a[j + 1];
                a[j + 1] = T;
            }
        }
    }
}

void swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}
struct PGMImage {
    int H, W, MaxGray;
    string Comment;
    string MagicNo;
    int ImageData[500][500];
    //vector<vector<int> > ImageData;

    PGMImage() {
        cout << "Called Automatically" << endl;
        H = W = MaxGray = -1;
    }


    //bool ReserveMemory() {
    //    // Code to create memory storage for the image
    //    // This code assumes that H and W have been set earlier
    //    cout << W << " " << H << endl;
    //    if (H < 0 || W < 0)
    //        return false;
    //    Create(ImageData, H, W);
    //    return true;
    //}

    bool LoadImage(char FileName[]) {
        // Code to open File, Reserve Memory and load image data in memory
        ifstream FIN(FileName);
        if (!FIN.is_open())
            return false;

        getline(FIN, MagicNo);
        getline(FIN, Comment); // reading the comment. PROBLEM HERE THE COMMENTIS OPTIONAL

        FIN >> W >> H >> MaxGray;
        /*if( !ReserveMemory()){
            FIN.close();
            return false;
        }*/

        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                FIN >> ImageData[r][c];
            }
        }

        FIN.close();
        return true;
    }

    bool SaveImage(char FileName[]) {
        // Code to open File, Reserve Memory and load image data in memory
        if (H < 0)
            return false;

        ofstream FOUT(FileName);
        // Your Code to check if the file has been created for output
        // If File not created then return false

        FOUT << "P2" << endl
            << "# Created By 21L-6236 and 21L-6256" << endl
            << W << " " << H << endl
            << MaxGray << endl;

        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                FOUT << ImageData[r][c] << " ";
            }
            FOUT << endl;
        }
        FOUT.close();
        return true;
    }

    bool Create_Negative() {
        if (H < 0)
            return false;
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++)
                ImageData[r][c] = MaxGray - ImageData[r][c];
        }
        return true;
    }

    bool Mean_Filter(int FilterSize) {
        if (H < 0)
            return false;
        int Temp[500][500];
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                int k = 0;
                int SUM = 0;
                for (int i = r - FilterSize / 2; i < r + FilterSize / 2; i++) {
                    for (int j = c - FilterSize / 2; j < c + FilterSize / 2; j++) {
                        if (i >= 0 && i < H && j >= 0 && j < W) {
                            SUM += ImageData[i][j];
                            k++;
                        }
                    }
                }
                Temp[r][c] = SUM / k;
            }
        }
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                ImageData[r][c] = Temp[r][c];
            }
        }
    }

    bool Median_Filter(int FilterSize) {
        if (H < 0)
            return false;
        int Temp[500][500];
        int D[100];
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                int k = 0;
                for (int i = r - FilterSize / 2; i < r + FilterSize / 2; i++) {
                    for (int j = c - FilterSize / 2; j < c + FilterSize / 2; j++) {
                        if (i >= 0 && i < H && j >= 0 && j < W) {
                            D[k] = ImageData[i][j];
                            k++;
                        }
                    }
                }
                B_Sort(D, k);
                Temp[r][c] = D[k / 2];
            }
        }
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                ImageData[r][c] = Temp[r][c];
            }
        }
        return true;
    }

    bool Rotate(double angle) {
    	int Temp[500][500];
            for(int r = 0; r < H; r++){
          		  for(int c = 0; c < W ; c++){
          		  	int newr = r * cos (angle) + c * sin ( angle );
          		  	int newc = -r * sin(angle) + c * cos(angle);
          		  		if ( newr > 0 && newr < H && newc > 0 && newc < W )
          		  			Temp[r][c] = ImageData[newr][newc];
          		  }
          	}
    	
    	 for(int r = 0; r < H; r++){
            for(int c = 0; c < W ; c++){
                ImageData[r][c] = Temp[r][c];
            }
        }
        return true;
    }

    bool RotateClockwise() {
    	int Temp[500][500];
	    for(int r = 0; r < W; r++){
	        for(int c = 0; c < H; c++){
	            Temp[r][c] = ImageData[c][r];
	        }
	    }
	    for (int r = 0; r < H; r++) {
            int start = 0;
			int end = W - 1;
	
			while (start < end) {
	
				swap(&Temp[r][start], &Temp[r][end]);
				start++;
				end--;
			}
        }
        for(int r = 0; r < H; r++){
            for(int c = 0; c < W ; c++){
                ImageData[r][c] = Temp[r][c];
            }
        }
        return true;
    }

    bool RotateCounterClockwise() {
		int Temp[500][500];
	    for(int r = 0; r < W; r++){
	        for(int c = 0; c < H; c++){
	            Temp[r][c] = ImageData[c][r];
	        }
	    }
	    for (int c = 0; c < W; c++) {
            int start = 0;
			int end = H - 1;
	
			while (start < end) {
	
				swap(&Temp[start][c], &Temp[end][c]);
				start++;
				end--;
			}
        }
        for(int r = 0; r < H; r++){
            for(int c = 0; c < W ; c++){
                ImageData[r][c] = Temp[r][c];
            }
        }
        return true;
    }

    bool FlipHorizontal() {
		for (int r = 0; r < H; r++) {
            int start = 0;
			int end = W - 1;
	
			while (start < end) {
	
				swap(&ImageData[r][start], &ImageData[r][end]);
				start++;
				end--;
			}
        }
        
        return true;
    }

    bool FlipVertical() {
		for (int c = 0; c < W; c++) {
            int start = 0;
			int end = H - 1;
	
			while (start < end) {
	
				swap(&ImageData[start][c], &ImageData[end][c]);
				start++;
				end--;
			}
        }
        return true;
    }

    bool Resize(int NewH, int NewW) {
		
        return true;
    }

    bool CropImage(int Left, int Top, int Right, int Bottom) {
		
        return true;
    }

    
};

int Menu() {
    int choice;
    do {
        cout << endl << "__________________________" << endl << endl
			<< "1. Load Image" << endl
            << "2. Save Image" << endl
            << "__________________________" << endl << endl
            << "3. Create Negative Image" << endl
            << "__________________________" << endl << endl
            << "4. Mean Filter" << endl
            << "5. Median Filter" << endl
            << "__________________________" << endl << endl
            << "6. Flip Horizontal" << endl
            << "7. Flip Vertical" << endl
            << "8. Rotate Clockwise by 90 Degree" << endl
            << "9. Rotate Counter Clockwise by 90 degree" << endl
            << "10. Rotate By arbitrary angle" << endl
            << "11. Resize Image" << endl
            << "12. Crop Image" << endl
            << "__________________________" << endl << endl
            << "13. Exit" << endl << endl
            << "Enter Your Choice: ";
        cin >> choice;
    } while (choice < 1 || choice > 13);
}

int main()
{
    PGMImage Image;

    char FileName[100];
    int Choice;

    do {
        Choice = Menu();
        if (Choice == 1) {
            cout << "Enter File Name ";
            cin >> FileName;
            if (Image.LoadImage(FileName))
                cout << "Image Loaded Successfully " << endl;
            else
                cout << "Image Not Loaded Successfully " << endl;
        }
        else if (Choice == 2) {
            cout << "Enter File Name ";
            cin >> FileName;
            if (Image.SaveImage(FileName))
                cout << "Image Saved Successfully " << endl;
            else
                cout << "Image Not Saved Successfully " << endl;

        }
        else if (Choice == 3) {
            if (Image.H < 0)
                cout << "No Image Loaded" << endl;
            else
                Image.Create_Negative();
        }
        else if (Choice == 4) {
        	int S;
            cout << "Filter Size ";
            cin >> S;
            Image.Mean_Filter(S);
        }
        else if (Choice == 5) {
            int S;
            cout << "Filter Size ";
            cin >> S;
            Image.Median_Filter(S);
        }
        else if (Choice == 6) {
			if(Image.H < 0)
				cout << "No Image Loaded" << endl;
			else
				Image.FlipHorizontal();
        }
        else if (Choice == 7) {
			if(Image.H < 0)
				cout << "No Image Loaded" << endl;
			else
				Image.FlipVertical();
        }
        else if (Choice == 8) {
			if(Image.H < 0)
				cout << "No Image Loaded" << endl;
			else
				Image.RotateClockwise();
        }
        else if (Choice == 9) {
			if(Image.H < 0)
				cout << "No Image Loaded" << endl;
			else
				Image.RotateCounterClockwise();
        }
        else if (Choice == 10) {
			if(Image.H < 0)
				cout << "No Image Loaded" << endl;
			else{
				double A;
	            cout << "Enter Angle: ";
	            cin >> A;
	            A = A * 3.1415 / 180;
	            Image.Rotate(A);
			}
        }
        else if (Choice == 11) {

        }
        else if (Choice == 12) {

        }

    } while (Choice != 13);

    return 0;
}

