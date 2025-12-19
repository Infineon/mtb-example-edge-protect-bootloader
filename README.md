# PSOC&trade; Edge MCU: Edge Protect Bootloader

This code example demonstrates the integration of the *PSOC_Edge_Protect_Bootloader* library with a user application or other code examples using *PSOC_Edge_Basic_Secure_App* as a reference implementation throughout this code example. This example demonstrates the usage of *PSOC_Edge_Protect_Bootloader* on Infineon's PSOC&trade; Edge MCU for secure boot and secure firmware update. 

*PSOC_Edge_Protect_Bootloader* is an open-source MCUboot library-based bootloader for Infineon's PSOC&trade; Edge MCU. MCUboot is the primary bootloader in popular IoT operating systems, such as Zephyr and Apache Mynewt.

Although the instructions are demonstrated with PSOC_Edge_Basic_Secure_App, they are applicable to other code examples as well.

This code example has a three project structure: CM33 secure, CM33 non-secure, and CM55 projects. All three projects are programmed to the external QSPI flash and executed in Execute in Place (XIP) mode. Extended boot launches the CM33 secure project from a fixed location in the external flash, which then configures the protection settings and launches the CM33 non-secure application. Additionally, CM33 non-secure application enables CM55 CPU and launches the CM55 application.

[View this README on GitHub.](https://github.com/Infineon/mtb-example-edge-protect-bootloader)

[Provide feedback on this code example.](https://yourvoice.infineon.com/jfe/form/SV_1NTns53sK2yiljn?Q_EED=eyJVbmlxdWUgRG9jIElkIjoiQ0UyMzUzNzkiLCJTcGVjIE51bWJlciI6IjAwMi0zNTM3OSIsIkRvYyBUaXRsZSI6IlBTT0MmdHJhZGU7IEVkZ2UgTUNVOiBFZGdlIFByb3RlY3QgQm9vdGxvYWRlciIsInJpZCI6ImFydGVtLmRvdmhhbEBpbmZpbmVvbi5jb20iLCJEb2MgdmVyc2lvbiI6IjIuMi4wIiwiRG9jIExhbmd1YWdlIjoiRW5nbGlzaCIsIkRvYyBEaXZpc2lvbiI6Ik1DRCIsIkRvYyBCVSI6IklDVyIsIkRvYyBGYW1pbHkiOiJQU09DIn0=)


## Requirements

- [ModusToolbox&trade;](https://www.infineon.com/modustoolbox) v3.6 or later (tested with v3.6)
- Board support package (BSP) minimum required version for:
   - KIT_PSE84_EVAL_EPC2: v1.0.0
   - KIT_PSE84_EVAL_EPC4: v1.0.0
   - KIT_PSE84_AI: v1.0.0
- Programming language: C
- Associated parts: All [PSOC&trade; Edge E84 MCU](https://www.infineon.com/products/microcontroller/32-bit-psoc-arm-cortex/32-bit-psoc-edge-arm/psoc-edge-e84) parts


## Supported toolchains (make variable 'TOOLCHAIN')

- GNU Arm&reg; Embedded Compiler v14.2.1 (`GCC_ARM`) – Default value of `TOOLCHAIN`
- Arm&reg; Compiler v6.22 (`ARM`)
- IAR C/C++ Compiler v9.50.2 (`IAR`)

## Supported kits (make variable 'TARGET')

- **PSOC&trade; Edge E84 Evaluation Kit** (minimum required revision: Rev *D) <br>
    - [PSOC&trade; Edge E84 Evaluation Kit](https://www.infineon.com/KIT_PSE84_EVAL) (`KIT_PSE84_EVAL_EPC2`) – Default value of `TARGET`
    - [PSOC&trade; Edge E84 Evaluation Kit](https://www.infineon.com/KIT_PSE84_EVAL) (`KIT_PSE84_EVAL_EPC4`)
    - [PSOC&trade; Edge E84 AI Kit](https://www.infineon.com/KIT_PSE84_AI) (`KIT_PSE84_AI`)


## Hardware setup

See the kit user guide to ensure that the board is configured correctly to boot from the RRAM location.

Ensure the following jumper and pin configuration on board.
- BOOT SW must be in the LOW/OFF position
- J20 and J21 must be in the tristate/not connected (NC) position

For the `KIT_PSE84_AI` kit, either remove the R188 resistor and populate the R187 resistor to pull the boot pin to LOW, or follow the provisioning method in the [Provisioning method](#provisioning-method) section to avoid hardware rework.

> **Note:** To evaluate the other supported code examples that boot from QSPI flash, the resistors should be reverted to default settings.

> **Note:** To start this code example, the device should be in DEVELOPMENT LCS and secure_boot disabled. If you have just unboxed the device, it is already in DEVELOPMENT LCS with secure_boot disabled. In case if you have already enabled secure boot, revert back your changes (disable secure boot in policy and provision the device).


## Software setup

See the [ModusToolbox&trade; tools package installation guide](https://www.infineon.com/ModusToolboxInstallguide) for information about installing and configuring the tools package.

- Install a terminal emulator if you do not have one. Instructions in this document use [Tera Term](https://teratermproject.github.io/index-en.html)
 
- Edge Protect Tools: Install Edge Protect Security Suite v1.6 or later. See [Getting started with PSOC&trade; Edge E8 MCU on ModusToolbox&trade; software](https://www.infineon.com/AN235935) for detailed installation instructions


## Provisioning method

To avoid hardware rework on the `KIT_PSE84_AI` kit, customize the generated OEM policy JSON file to ignore the boot pin status while booting.

While following the provisioning steps, once the OEM key pair is generated, set the 'oem_alt_boot' to "false" in the *policy/policy_oem_provisioning.json* file in the project before provisioning the kit.

For detailed instructions to provision the kit, see the *Development flow* section in the [AN237849 – Getting started with PSOC&trade; Edge security](https://www.infineon.com/AN237849).

> **Note:** To evaluate other code examples that boot from QSPI flash, reprovision the kit with default settings by setting 'oem_alt_boot' to "true" in the *policy/policy_oem_provisioning.json* file in the project before reprovisioning the kit.


## Getting started with PSOC_Edge_Protect_Bootloader

*PSOC_Edge_Protect_Bootloader* is configured to run from RRAM by default. Using the default configuration is the easiest way to get started. 

On power on, Secure Enclave starts first, which then launches the Extended Boot on the CM33 CPU. Extended Boot is responsible for launching the first user code. In this code example, *PSOC_Edge_Protect_Bootloader* is the first user code followed by the application of your choice, such as [Hello world](https://github.com/Infineon/mtb-example-psoc-edge-hello-world) and [PSOC_Edge_Basic_Secure_App](https://github.com/Infineon/mtb-example-psoc-edge-basic-secure-app) code examples.

To experience the full bootchain with *PSOC_Edge_Protect_Bootloader*, add Edge Protect Bootloader to an existing application. This example uses the *PSOC_Edge_Basic_Secure_App* code example as the reference starting point. To use the bootloader with an application, perform the following: 

1. Create [PSOC_Edge_Basic_Secure_App](https://github.com/Infineon/mtb-example-psoc-edge-basic-secure-app) and PSOC_Edge_Protect_Bootloader code examples
2. Add Edge Protect Bootloader to PSOC_Edge_Basic_Secure_App code example
3. Configure the Memory Map and Makefiles  
4. Build, program, and run

Follow the detailed steps given in the [Operation](#operation) section.


## Operation

### Create PSOC_Edge_Protect_Bootloader
1. Create the *PSOC_Edge_Protect_Bootloader* code example. See [Using the code example](docs/using_the_code_example.md) for instructions on creating a project and opening it in various supported IDEs

### Create PSOC_Edge_Basic_Secure_App
2. If you have already created the *PSOC_Edge_Basic_Secure_App* code example, you can skip this step. If you have not created it yet, see [Using the code example](docs/using_the_code_example.md) for instructions on creating a project and opening it in various supported IDEs

   Now, you can see both **PSOC_Edge_Protect_Bootloader** and **PSOC_Edge_Basic_Secure_App** code examples in the **Project Explorer** of your IDE as shown in **Figure 1**

   **Figure 1. Creating applications**

   ![](images/create_application.png)

#### Add PSOC_Edge_Protect_Bootloader to PSOC_Edge_Basic_Secure_App
   To facilitate a seamless usage of **PSOC_Edge_Basic_Secure_App** and **PSOC_Edge_Protect_Bootloader**, it is essential that the **PSOC_Edge_Protect_Bootloader** possesses a comprehensive understanding of the PSOC_Edge_Basic_Secure_App's configuration parameters, such as its location and size

   To establish this connection, import **PSOC_Edge_Protect_Bootloader** as a project within the **PSOC_Edge_Basic_Secure_App**. The subsequent instructions will provide a detailed walkthrough of this integration process

3. In **File Explorer**, navigate to the workspace or directory where you have created **PSOC_Edge_Basic_Secure_App** and **PSOC_Edge_Protect_Bootloader** applications

4. Copy the *proj_bootloader* from **PSOC_Edge_Protect_Bootloader** to the root of **PSOC_Edge_Basic_Secure_App** as shown in **Figure 2** and **Figure 3**

   **Figure 2. Copy bootloader**

   ![](images/copy_bl.png)

   **Figure 3. Paste bootloader**

   ![](images/paste_epb.png)

5. While copying, the **Copy Project** window will display as shown in **Figure 4**. Change the Project Name to *PSOC_Edge_Basic_Secure_App.proj_bootloader*. Uncheck the **Use default location** and select the path to *PSOC_Edge_Basic_Secure_App*. Append *\proj_bootloader* to the path as shown in **Figure 4** and then click **Copy**

   **Figure 4. Rename project while copying**

   ![](images/rename_copy.png)

6. Select the *PSOC_Edge_Basic_Secure_App* application, navigate to Quick Panel and generate the launch configurations as shown in **Figure 5**

   **Figure 5. Generate launch configurations**

   ![](images/generate_launch.png)

   > **Note:** Earlier steps refer to *PSOC_Edge_Basic_Secure_App*. However, the process of adding a bootloader to other application is same, with a difference that wherever you have *PSOC_Edge_Basic_Secure_App*, you must select your application

7. Update the *Makefile*. Open *Makefile* in the root of the **PSOC_Edge_Basic_Secure_App** and add `proj_bootloader` to `MTB_PROJECTS` variable as follows:

   ``` 
   MTB_PROJECTS=proj_cm33_s proj_cm33_ns proj_cm55 proj_bootloader
   ```

#### Configure the Memory Map and Makefiles
   The *PSOC_Edge_Basic_Secure_App* code example bundles a custom *design.modus* file compatible with *PSOC_Edge_Protect_Bootloader*. Therefore, do not make any further customizations here to use *PSOC_Edge_Edge_Protect_Bootloader* and *PSOC_Edge_Basic_Secure_App* together.

8. Open *common.mk* in the root of the application and update *COMBINE_SIGN_JSON* to *boot_with_bldr.json* generated by the configurator and save the file

   ```
   COMBINE_SIGN_JSON?=./bsps/TARGET_$(TARGET)/config/GeneratedSource/boot_with_bldr.json
   ```

#### Build, program, and run 
9. Connect the board to your PC using the provided USB cable through the KitProg3 USB connector

10. Open a terminal program and select the KitProg3 COM port. Set the serial port parameters to 8N1 and 115200 baud

11. See [Using the code example](docs/using_the_code_example.md) for instructions on opening it in various supported IDEs, and performing tasks, such as building, programming, and debugging the application within the respective IDEs
 
12. Observe the console logs and confirm that the bootloader has started and the application has been launched by the bootloader

    **Figure 6. Application boot**

    ![](images/boot_without_security.png)

#### Perform updates
13. Open *common.mk* in the root of the application and update *COMBINE_SIGN_JSON* to *boot_with_bldr_upgr.json* generated by the configurator and save the file

     ```
     COMBINE_SIGN_JSON?=./bsps/TARGET_$(TARGET)/config/GeneratedSource/boot_with_bldr_upgr.json
     ```

14. See [Using the code example](docs/using_the_code_example.md) for instructions on opening it in various supported IDEs and performing tasks such as building, programming, and debugging the application within the respective IDEs

    > **Note:** 

     - In this step, images are built for execution from the primary slot, but they are programmed to the respective secondary slot. For details of primary and secondary slots, visit the **Memory** and **Solution** tabs in the Device Configurator. Upon successful programming, the device resets and the Edge Protect Bootloader starts the execution. The bootloader then copies images from the secondary slot to the primary slot and launches the application

     - The default configurator of this code example demonstrates updating with the overwrite mode

15. Observe that the console logs and confirm that the bootloader has started and the application has been launched by the bootloader

    **Figure 7. Application update**

    ![](images/update_without_security.png)


### Use other bootloader capabilities

*PSOC_Edge_Protect_Bootloader* provides several other capabilities including secured boot, secured updated with overwrite and swap, encrypted boot, and loading application to SRAM, etc. Utilize the self-help resources provided through the Bootloader Solution Personality feature, accessible within the Device Configurator UI, for guidance.


### Bootloader integration with LLVM-compiled applications

The Edge Protect Bootloader is not compatible with the LLVM Compiler. However, when you add the bootloader to a code example that utilizes the LLVM Compiler, the bootloader will also be conﬁgured to build with LLVM. To resolve this issue, manually override the compiler option in the bootloader’s *Makeﬁle*, as follows:

```
TOOLCHAIN=<GCC_ARM> or <ARM> or <IAR>
```

By configuring the bootloader to use a custom compiler, it will be compiled separately while the application continues to build with the selected LLVM Compiler specified in the *common.mk* file.


## Related resources

Resources  | Links
-----------|----------------------------------
Application notes  | [AN235935](https://www.infineon.com/AN235935) – Getting started with PSOC&trade; Edge E8 MCU on ModusToolbox&trade; software <br> [AN237857](https://www.infineon.com/assets/row/public/documents/30/42/infineon-an237857-edge-protect-bootloader-psoc-edge-applicationnotes-en.pdf) – Edge Protect Bootloader for PSOC&trade; Edge MCU
Code examples  | [Using ModusToolbox&trade;](https://github.com/Infineon/Code-Examples-for-ModusToolbox-Software) on GitHub
Device documentation | [PSOC&trade; Edge E84 MCU datasheet](https://www.infineon.com/products/microcontroller/32-bit-psoc-arm-cortex/32-bit-psoc-edge-arm/psoc-edge-e84#Documents) <br> [PSOC&trade; Edge E84 MCU reference manuals](https://www.infineon.com/products/microcontroller/32-bit-psoc-arm-cortex/32-bit-psoc-edge-arm/psoc-edge-e84#Documents)
Development kits | Select your kits from the [Evaluation board finder](https://www.infineon.com/cms/en/design-support/finder-selection-tools/product-finder/evaluation-board)
Libraries  | [mtb-dsl-pse8xxgp](https://github.com/Infineon/mtb-dsl-pse8xxgp) – Device support library for PSE8XXGP <br> [retarget-io](https://github.com/Infineon/retarget-io) – Utility library to retarget STDIO messages to a UART port
Tools  | [ModusToolbox&trade;](https://www.infineon.com/modustoolbox) – ModusToolbox&trade; software is a collection of easy-to-use libraries and tools enabling rapid development with Infineon MCUs for applications ranging from wireless and cloud-connected systems, edge AI/ML, embedded sense and control, to wired USB connectivity using PSOC&trade; Industrial/IoT MCUs, AIROC&trade; Wi-Fi and Bluetooth&reg; connectivity devices, XMC&trade; Industrial MCUs, and EZ-USB&trade;/EZ-PD&trade; wired connectivity controllers. ModusToolbox&trade; incorporates a comprehensive set of BSPs, HAL, libraries, configuration tools, and provides support for industry-standard IDEs to fast-track your embedded application development

<br>


## Other resources

Infineon provides a wealth of data at [www.infineon.com](https://www.infineon.com) to help you select the right device, and quickly and effectively integrate it into your design.


## Document history

Document title: *CE235379* – *PSOC&trade; Edge MCU: Edge Protect Bootloader*

 Version | Description of change
 ------- | ---------------------
 1.x.0   | New code example <br> Early access release
 2.0.0   | GitHub release
 2.0.1   | Use se-rt-services-utils from BSP
 2.1.0   | SE RAMApp Staging for EPC4 (CM0 RAMApp) support <br>  Code execution from CM33 SRAM and external memory (EPC2, EPC4) <br> Multi-key multi-image XIP encryption (EPC2, EPC4) support  <br> Image encryption with SE RT Services API (EPC4)
 2.2.0   | Added KIT_PSE84_AI kit support 
<br>


All referenced product or service names and trademarks are the property of their respective owners.

The Bluetooth&reg; word mark and logos are registered trademarks owned by Bluetooth SIG, Inc., and any use of such marks by Infineon is under license.

PSOC&trade;, formerly known as PSoC&trade;, is a trademark of Infineon Technologies. Any references to PSoC&trade; in this document or others shall be deemed to refer to PSOC&trade;.

---------------------------------------------------------

(c) 2025, Infineon Technologies AG, or an affiliate of Infineon Technologies AG. All rights reserved.
This software, associated documentation and materials ("Software") is owned by Infineon Technologies AG or one of its affiliates ("Infineon") and is protected by and subject to worldwide patent protection, worldwide copyright laws, and international treaty provisions. Therefore, you may use this Software only as provided in the license agreement accompanying the software package from which you obtained this Software. If no license agreement applies, then any use, reproduction, modification, translation, or compilation of this Software is prohibited without the express written permission of Infineon.
<br>
Disclaimer: UNLESS OTHERWISE EXPRESSLY AGREED WITH INFINEON, THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, ALL WARRANTIES OF NON-INFRINGEMENT OF THIRD-PARTY RIGHTS AND IMPLIED WARRANTIES SUCH AS WARRANTIES OF FITNESS FOR A SPECIFIC USE/PURPOSE OR MERCHANTABILITY. Infineon reserves the right to make changes to the Software without notice. You are responsible for properly designing, programming, and testing the functionality and safety of your intended application of the Software, as well as complying with any legal requirements related to its use. Infineon does not guarantee that the Software will be free from intrusion, data theft or loss, or other breaches (“Security Breaches”), and Infineon shall have no liability arising out of any Security Breaches. Unless otherwise explicitly approved by Infineon, the Software may not be used in any application where a failure of the Product or any consequences of the use thereof can reasonably be expected to result in personal injury.
