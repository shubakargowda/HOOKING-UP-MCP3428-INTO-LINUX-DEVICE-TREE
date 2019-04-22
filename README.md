# HOOKING-UP-MCP3428-INTO-LINUX-DEVICE-TREE
It contains how to hook up MCP3428 I2C Slave Device into S5P4418 device tree

Following are the steps to hook up MCP3428 I2C ADC Chip into the nanopi2 device tree.

Step 1 : See the Documentation of the ADC MCP3428 Chip under Documention/device-tree-bindings/iio/adc/mcp3422.txt

    * Microchip mcp3422/3/4/6/7/8 chip family (ADC)

Required properties:
 - compatible: Should be
	"microchip,mcp3422" or
	"microchip,mcp3423" or
	"microchip,mcp3424" or
	"microchip,mcp3426" or
	"microchip,mcp3427" or
	"microchip,mcp3428"
 - reg: I2C address for the device

Example:
adc@0 {
	compatible = "microchip,mcp3424";
	reg = <0x68>;
};

Step 2 : Add this device as a child node for the I2C0 Controoler Node which is as follows.

i2c_0: i2c@c00a4000 {
			samsung,i2c-max-bus-freq = <400000>;
			status = "okay";

			#address-cells = <1>;
			#size-cells = <0>;

			es8316: es8316@11 {
				#sound-dai-cells = <0>;
				compatible = "everest,es8316";
				reg = <0x11>;
			};

                                mcp3428@68 {
                                   
                                         compatible = "microchip,mcp3428";
                                          reg = <0x68>;
                                      };
		};
    
Step 4 : Integrate the ADC Chip Driver into the kernel. Following are the two ways to acheive this.

1. Add the line CONFIG_MCP3428=y into the configuration file of nanopi2(nanopi2_linux_deconfig).
2. using make menuconfig --> Device Drivers --> Industrial IO --> ADC --> Michrochip Technology MCP3422/24/28 Build this module into the Kernel.

Save the Configurations and Recompile the Kernel.

 Step 3 : Recompile the Kernel to make changes affected
 
 make ARCH=arm
 
 Step 4 : Copy the newly generated zImage and .dtb files into the storage media(/boot directory).
 
 Step 5 : Since I2C Devices are not hotplug devices (Cannot Detect Dynamically) So we need to explicitly specify the I2C device    driver modules to load at boot time. here is the steps to do.

1. Using modprobe command modprobe i2c-dev.ko

2. Edit the file in the target sudo nano /etc/modules and specify the i2c-adapter driver, i2c-bus driver, to load at boot time.

 i2c-adapter
 i2c-nexell
 i2c-dev
 
 Step 5 : Make sure that your device should be connected before your board boot up.
 
 Step 6 : Test the Device is detected or not using builtin i2c-tools like as follows.
 
       i2cdetect -y 0
       
       After executing this command u will the chip address as 0x68 which is my i2c chip device address.
       
Step 7 : Communicate with the device using the userspace Application.


 
