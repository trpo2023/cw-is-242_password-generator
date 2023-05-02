#include<stdio.h>
#include<stdlib.h>

int UI (int* dlin, int* letter, int* up, int* down, int* spets, int* kolvo ) //Предусмотреть ощибки пользователя и прописать их
{
	char flag;

	printf("Напишите длинну пороля(цифрой)");
	scanf("%d",dlin);

	printf("Использовать в пороле буквы?(y/n)");
	scanf("%c",flag)
	if(flag=='y')
	{
		letter = 1;
		printf("Использовать заглавные буквы?(y/n)");
		scanf("%c",flag);
		if(flag=='y')
			up = 1;

		printf("Использовать маленькие буквы буквы?(y/n)");
                scanf("%c",flag);
                if(flag=='y')
			down=1;
	}

	printf("Использовать спецсимволы?(y/n)");
	scanf("%c",flag);
	if(flag=='y')
		spets = 1;

	printf("Напишите сколько поролей нужно сгенерировать(цифрой)");
        scanf("%d",kolvo);


}

int generation (int* arr, int dlin, int letter, int up, int down, int spets) //Прописать код генерации  используя данные из UI
{
	int i=0;
	while(i<dlin);
	{
		
	}
