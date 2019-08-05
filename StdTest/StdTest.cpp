// ÄãºÃ

#include "stdafx.h"

#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <list>
#include <map>

#include "hidapi.h"
#include "libusb.h"

#pragma comment(lib, "hidapi.lib")
#pragma comment(lib, "libusb-1.0.lib")

void clocking(void(*func)(void))
{
	clock_t start = clock();

	func();

	clock_t end = clock();
	printf("%lf\n", (double)(end - start) / CLK_TCK);
}

void findEndPoint(libusb_device* dev, uint8_t & endpoint_in, uint8_t & endpoint_out)
{
	libusb_config_descriptor* conf_desc;
	int r = libusb_get_config_descriptor(dev, 0, &conf_desc);

	int a = conf_desc->bNumInterfaces;
	for (int i = 0; i < a; ++i)
	{
		int b = conf_desc->interface[i].num_altsetting;
		for (int j = 0; j < b; ++j)
		{
			int c = conf_desc->interface[i].altsetting[j].bNumEndpoints;
			for (int k = 0; k < c; ++k)
			{
				const libusb_endpoint_descriptor* endpoint = &conf_desc->interface[i].altsetting[j].endpoint[k];
				if (endpoint->bEndpointAddress & LIBUSB_ENDPOINT_IN)
				{
					endpoint_in = endpoint->bEndpointAddress;
					printf("bInterval in : %d\n", endpoint->bInterval);
				}
				else
				{
					endpoint_out = endpoint->bEndpointAddress;
					printf("bInterval out : %d\n", endpoint->bInterval);
				}
			}
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	// from VS2010

	/*int time = 60 * 60 ;
	int fps = 54;
	int imgsize = 1280 * 960;
	
	unsigned char* img = new unsigned char[imgsize];
	memset(img, imgsize, '0');
	std::vector<std::vector<unsigned char>> MatCache;
	for (int i = 0; i < time * fps; ++i)
	{
		std::vector<unsigned char> imgCache;
		imgCache.assign(img, img + imgsize);
		if (0 == i)
			imgCache[0] = '1';
		try
		{
			MatCache.push_back(imgCache);
		}
		catch (...)
		{
			break;
		}
	}
	printf("%d\n", MatCache.size());*/

	/*libusb_context* ctx = 0;
	int r = libusb_init(&ctx);

	static bool haveV100 = false, haveV200 = false;

	while (true)
	{
		libusb_device *tmp_dev, **tmp_devs;
		int cnt = libusb_get_device_list(ctx, &tmp_devs), idx = 0;
		if (cnt <= 0)
			return -1;

		bool tmp_checkV100 = false, tmp_checkV200 = false, tmp_checkV200Cam = false;
		while ((tmp_dev = tmp_devs[idx++]) != NULL)
		{
			libusb_device_descriptor desc;
			if (libusb_get_device_descriptor(tmp_dev, &desc) < 0)
			{
				printf("%failed this time\n");
				continue;
			}

			if (desc.idVendor == 0x4448 && desc.idProduct == 0x5670)
			{
				tmp_checkV100 = true;
			}
			else if (desc.idVendor == 0x0483 && desc.idProduct == 0x5750)
			{
				tmp_checkV200 = true;
			}
			else if (desc.idVendor == 0x2ba2 && desc.idProduct == 0x4d55)
			{
				tmp_checkV200Cam = true;
			}
		}

		if (tmp_checkV100 != haveV100)
		{
			if (tmp_checkV100 && !haveV100)										// V100 had plugin
			{
				printf("V100 had plugin\n");
			}
			else if (!tmp_checkV100 && haveV100)								// V100 had plugout
			{
				printf("V100 had plugout\n");
			}
			haveV100 = tmp_checkV100;
		}

		if ((tmp_checkV200 & tmp_checkV200Cam) != haveV200)
		{
			if (tmp_checkV200 && tmp_checkV200Cam && !haveV200)					// V200 had plugin
			{
				printf("V200 had plugin\n");
			}
			else if ((!tmp_checkV200 || !tmp_checkV200Cam) && haveV200)			// V200 had plugout
			{
				printf("V200 had plugout\n");
			}
			haveV200 = tmp_checkV200 & tmp_checkV200Cam;
		}

		libusb_free_device_list(tmp_devs, 1);
	}

	libusb_device_handle* handle = libusb_open_device_with_vid_pid(ctx, 0x0483, 0x5750);
	if (!handle)
	{
		printf("no device!\n");
		system("pause");
		return -1;
	}

	if (r = libusb_kernel_driver_active(handle, 0))
		r = libusb_detach_kernel_driver(handle, 0);
	r = libusb_claim_interface(handle, 0);

	libusb_device* dev = libusb_get_device(handle);

	uint8_t endpoint_in = 0x81, endpoint_out = 0x01;
	findEndPoint(dev, endpoint_in, endpoint_out);

	printf("endpoint_in : 0x%02x endpoint_out : 0x%02x\n\n", endpoint_in, endpoint_out);
	clock_t begin = clock();
	for (int i = 0; i < 32; ++i)
	{
		unsigned char testdata[] = "M01*****0000000000000000000000000000*1111****033411************A";
		int datasize = sizeof(testdata) / sizeof(unsigned char);

		int write_transfer = 0, read_transfer = 0;

		clock_t writebegin = clock();
		int write = libusb_bulk_transfer(handle, endpoint_out, testdata, datasize - 1, &write_transfer, 0);
		clock_t writeend = clock();
		printf("writetime : %lf\t", (double)(writeend - writebegin) / CLK_TCK);

		clock_t readbegin = clock();
		int read = libusb_bulk_transfer(handle, endpoint_in, testdata, datasize, &read_transfer, 0);
		clock_t readend = clock();
		printf("readtime : %lf\n", (double)(readend - readbegin) / CLK_TCK);

		printf("recvdata : %s\n", testdata);
		printf("write_transfer : %d\tread_transfer : %d\n", write_transfer, read_transfer);
		printf("write : %d\tread : %d\n\n", write, read);
	}
	clock_t end = clock();
	printf("writetime : %lf\t", (double)(end - begin) / CLK_TCK);*/

	/*hid_device* dev = hid_open(0x0483, 0x5750, 0);

	for (int i = 0; i < 100; ++i)
	{
	clock_t start = clock();
	unsigned char data[] = "\0M01*****0000000000000000000000000000*1111****033411************A";
	int res = hid_write(dev, data, sizeof(data) / sizeof(unsigned char)-1);
	clock_t end = clock();
	printf("%lf\t", (double)(end - start) / CLOCKS_PER_SEC);
	start = clock();
	res = hid_read_timeout(dev, data, sizeof(data) / sizeof(unsigned char), 500);
	end = clock();
	printf("%lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	}*/

	/*int r = libusb_init(0);
	test_mode = USE_HID;
	test_device(0x0483, 0x5750);*/

	/*int r = libusb_init(0);

	libusb_device_handle* handle = libusb_open_device_with_vid_pid(0, 0x0483, 0x5750);
	libusb_device* dev = libusb_get_device(handle);

	unsigned char bus = libusb_get_bus_number(dev);

	libusb_device_descriptor dev_desc;
	bool a = libusb_get_device_descriptor(dev, &dev_desc) == LIBUSB_SUCCESS;

	libusb_bos_descriptor *bos_desc;
	libusb_get_bos_descriptor(handle, &bos_desc);

	libusb_config_descriptor *conf_desc;
	libusb_get_config_descriptor(dev, 0, &conf_desc);*/

	/*hid_device* dev = hid_open(0x0483, 0x5750, 0);

	for (int i = 0; i < 100; ++i)
	{
	clock_t start = clock();
	unsigned char data[] = "\0M01*****0000000000000000000000000000*1111****033411************A";
	int res = hid_write(dev, data, sizeof(data) / sizeof(unsigned char)-1);
	clock_t end = clock();
	printf("%lf\t", (double)(end - start) / CLOCKS_PER_SEC);
	start = clock();
	res = hid_read_timeout(dev, data, sizeof(data) / sizeof(unsigned char), 500);
	end = clock();
	printf("%lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	}*/

	/*libusb_device** devs;
	libusb_device* dev;
	int i = 0;

	int r = libusb_init(0);
	if (r < 0)
	{
	printf("0\n");
	return -1;
	}

	int cnt = libusb_get_device_list(0, &devs);
	if (cnt < 0)
	{
	printf("1\n");
	return -1;
	}

	std::vector<libusb_device_descriptor> vec;
	while ((dev = devs[i++]) != 0)
	{
	libusb_device_descriptor desc;
	r = libusb_get_device_descriptor(dev, &desc);
	if (r < 0)
	{
	printf("2.%d\n", i);
	return -1;
	}
	vec.push_back(desc);
	}*/

	system("pause");
	return 0;
}
