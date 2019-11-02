#include <stdio.h>
#include <conio.h>

typedef struct{
	int roll;
	int age;
	int std;
	char name[1024];
}Student;

void input(Student *s){
	printf("\nEnter your roll: ");
	scanf("%d", &(s->roll));
	printf("Enter your age: ");
	scanf("%d", &(s->age));
	printf("Enter your class: ");
	scanf("%d", &(s->std));
	printf("Enter your name: ");
	fflush(stdin);
	gets(s->name);
}

void display(Student *s){
	printf("%-5d %-5d %-5d %-s\n", s->roll,
				       s->age,
				       s->std,
				       s->name);
}

void writeRecord(char filename[], Student *s){
	// Opening the file in append mode
	// such that we do not overwrite
	// existing records
	FILE *fp = fopen(filename, "ab");
	fwrite(s, sizeof(Student), 1, fp);
	fclose(fp);
}

void displayRecords(char filename[]){
	long size;
	Student temp;
	FILE *fp = fopen(filename, "rb");
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	printf("\n%-5s %-5s %-5s %-s\n", "ROLL", "AGE", "CLASS", "NAME");
	// We run the loop till the file pointer
	// is less than the total size of the file
	while(ftell(fp) < size){
		fread(&temp, sizeof(Student), 1, fp);
		display(&temp);
	}
	fclose(fp);
}

void updateRecord(char filename[], int roll, Student *s){
	long size;
	Student temp;
	FILE *fp = fopen(filename, "rb+");
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	while(ftell(fp) < size){
		fread(&temp, sizeof(Student), 1, fp);
		if(temp.roll == roll){
			fseek(fp, ftell(fp) - sizeof(Student), SEEK_SET);
			fwrite(s, sizeof(Student), 1, fp);
			break;
		}
	}
	fclose(fp);
}

void deleteRecord(char filename[], int roll){
	long size;
	int total_records;
	Student temp;
	Student *arr = NULL;
	int index = 0;
	FILE *fp = fopen(filename, "rb");
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	total_records = size / sizeof(Student);
	arr = (Student*) malloc(sizeof(Student) * (total_records - 1));
	while(ftell(fp) < size){
		fread(&temp, sizeof(Student), 1, fp);
		if(temp.roll != roll){
			arr[index] = temp;
			index++;
		}
	}
	fclose(fp);
	fp = fopen(filename, "wb");
	fwrite(arr, sizeof(Student), total_records - 1, fp);
	fclose(fp);
	free(arr);
}

void searchRecords(char filename[], int roll){
	long size;
	int found = 0;
	Student temp;
	FILE *fp = fopen(filename, "rb");
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	while(ftell(fp) < size){
		fread(&temp, sizeof(Student), 1, fp);
		if(temp.roll == roll){
			found = 1;
			break;
		}
	}
	fclose(fp);
	if(found){
		printf("Record exists!!\n");
	}
	else{
		printf("Record not found!\n");
	}
}

int main(void)
{
	Student temp;
	int choice, roll;
	char filename[1024];
	clrscr();

	printf("Enter the name of the dbfile: ");
	gets(filename);

	do{
		printf("\nPress 1 to insert a Student record\n");
		printf("Press 2 to display the records\n");
		printf("Press 3 to update an existing record\n");
		printf("Press 4 to delete an existing record\n");
		printf("Press 5 to search for an record\n");
		printf("Press 6 to quit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				input(&temp);
				writeRecord(filename, &temp);
				break;
			case 2:
				displayRecords(filename);
				break;
			case 3:
				printf("\nEnter Student roll to update: ");
				scanf("%d", &roll);
				printf("Enter the updated records\n");
				input(&temp);
				updateRecord(filename, roll, &temp);
				break;
			case 4:	
				printf("\nEnter Student roll to delete: ");
				scanf("%d", &roll);
				deleteRecord(filename, roll);
				break;
			case 5:
				printf("\nEnter Student roll to search: ");
				scanf("%d", &roll);
				searchRecords(filename, roll);
				break;
			case 6:
				break;
			default:
				printf("Invalid choice!");
		}
	}
	while(choice != 6);
	return 0;
}