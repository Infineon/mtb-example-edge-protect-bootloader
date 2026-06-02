################################################################################
# \file Makefile
# \version 1.0
#
# \brief
# Makefile for configuring the Cortex-M33 core secure project
#
################################################################################
# \copyright
# (c) 2025-2026, Infineon Technologies AG, or an affiliate of Infineon
# Technologies AG.  SPDX-License-Identifier: Apache-2.0
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
################################################################################


include ../common.mk

################################################################################
# Basic Configuration
###############################################################################

# Name of application (used to derive name of final linked file).
#
# If APPNAME is edited, ensure to update or regenerate launch
# configurations for your IDE.
APPNAME=proj_bootloader

# If set to "true" or "1", display full command-lines when building.
VERBOSE=


################################################################################
# Advanced Configuration
################################################################################

# Enable optional code that is ordinarily disabled by default.
#
# Available components depend on the specific targeted hardware and firmware
# in use. In general, if you have
#
#    COMPONENTS=foo bar
#
# ... then code in directories named COMPONENT_foo and COMPONENT_bar will be
# added to the build
#
COMPONENTS+=SECURE_DEVICE


# Like COMPONENTS, but disable optional code that was enabled by default.
DISABLE_COMPONENTS+=

# Set this application to run at the CM0+
CORE=CM33
CORE_NAME=CM33_0

# Set this application to be secure
VCORE_ATTRS=SECURE

#Configure this application to be loaded into flash/ram. 
APPTYPE=flash

# By default the build system automatically looks in the Makefile's directory
# tree for source code and builds it. The SOURCES variable can be used to
# manually add source code to the build process from a location not searched
# by default, or otherwise not found by the build system.
SOURCES=

# Like SOURCES, but for include directories. Value should be paths to
# directories (without a leading -I).
INCLUDES=

# Add additional defines to the build process (without a leading -D).
DEFINES+=CYBSP_SKIP_SAU_INIT CYBSP_SKIP_MPC_INIT CYBSP_SKIP_MPU_INIT CYBSP_SKIP_PPC_INIT

# Disable SRF veneer and initialization code.
DEFINES+=MTB_SRF_CUSTOM_REQUEST_SUBMIT CYBSP_DISABLE_SRF_INIT

# Select softfp or hardfp floating point. Default is softfp.
VFP_SELECT+=

# Additional / custom C compiler flags.
#
# NOTE: Includes and defines should use the INCLUDES and DEFINES variable
# above.
CFLAGS+=

# Additional / custom C++ compiler flags.
#
# NOTE: Includes and defines should use the INCLUDES and DEFINES variable
# above.
CXXFLAGS+=

# Additional / custom assembler flags.
#
# NOTE: Includes and defines should use the INCLUDES and DEFINES variable
# above.
ASFLAGS+=

# Additional / custom linker flags.
LDFLAGS+=

# Additional / custom libraries to link in to the application.
LDLIBS+=

# Include personality-generated feature_config.mk early so that USE_MLDSA87
# and other variables are available before the ML-DSA block below.
-include ../bsps/TARGET_$(TARGET)/config/GeneratedSource/feature_config.mk

################################################################################
# ML-DSA-87 (Post-Quantum Cryptography) support via se-rt-services-utils PQC
# USE_MLDSA87, WOLFSSL_USER_SETTINGS, and MW_WOLFSSL are set by the
# personality-generated feature_config.mk when ML-DSA-87 is selected.
# This section adds WolfSSL sources/includes and public key auto-generation.
################################################################################

# WolfSSL root directory — resolved via SEARCH variable from ifx-wolfcrypto.mtb dep.
WOLFSSL_ROOT = $(SEARCH_ifx-wolfcrypto)

# Prevent ModusToolbox auto-discovery of all WolfSSL sources.
# We compile only the minimal set needed for ML-DSA verification.
CY_IGNORE += $(WOLFSSL_ROOT)

ifdef USE_MLDSA87

# WolfSSL sources for ML-DSA-87 verification (dilithium + SHA3/SHAKE + memory)
SOURCES += $(WOLFSSL_ROOT)/wolfcrypt/src/dilithium.c
SOURCES += $(WOLFSSL_ROOT)/wolfcrypt/src/sha3.c
SOURCES += $(WOLFSSL_ROOT)/wolfcrypt/src/memory.c

# ML-DSA-87 public key auto-generation via edgeprotecttools (Make restart pattern)
# Converts the DER public key to a C array compiled into the bootloader.
# MLDSA87_PUBLIC_KEY is set by personality-generated feature_config.mk
# (absolute path resolved by the Device Configurator).
MLDSA87_AUTOGEN_DIR := build/autogen

# Only generate when not running clean targets
ifeq ($(filter clean clean_proj,$(MAKECMDGOALS)),)

# Validate that MLDSA87_PUBLIC_KEY variable is set
ifeq ($(MLDSA87_PUBLIC_KEY),)
$(error [Bootloader] MLDSA87_PUBLIC_KEY is not set. Ensure feature_config.mk is generated by Device Configurator with ML-DSA-87 public key path configured.)
endif

# Validate that the ML-DSA-87 public key file exists
ifeq ($(wildcard $(MLDSA87_PUBLIC_KEY)),)
$(error [Bootloader] ML-DSA-87 public key file not found: $(MLDSA87_PUBLIC_KEY). Check mldsa_pub_key_path in Device Configurator.)
endif

$(MLDSA87_AUTOGEN_DIR)/ml_dsa_sign_key.c:
	@mkdir -p $(MLDSA87_AUTOGEN_DIR)
	@echo "[Bootloader] Converting ML-DSA-87 public key: $(MLDSA87_PUBLIC_KEY)"
	$(CY_TOOL_edgeprotecttools_EXE_ABS) convert-key --fmt C_ARRAY -k $(MLDSA87_PUBLIC_KEY) -o $@ --var-name mldsa87_pub_key

$(MLDSA87_AUTOGEN_DIR)/.ml_dsa_sign_key.mk: $(MLDSA87_AUTOGEN_DIR)/ml_dsa_sign_key.c
	@touch $@

-include $(MLDSA87_AUTOGEN_DIR)/.ml_dsa_sign_key.mk

SOURCES += $(MLDSA87_AUTOGEN_DIR)/ml_dsa_sign_key.c

endif

# WolfSSL include paths:
#   $(WOLFSSL_ROOT)                     - for <wolfssl/wolfcrypt/dilithium.h>
#   $(WOLFSSL_ROOT)/wolfssl/wolfcrypt   - for bare #include "dilithium.h"
#                                         (used by se-rt-services-utils ifx_se_psacrypto_pqc.c)
#   wolfssl/                            - for "user_settings.h"
INCLUDES += $(WOLFSSL_ROOT)
INCLUDES += $(WOLFSSL_ROOT)/wolfssl/wolfcrypt
INCLUDES += wolfssl

endif # USE_MLDSA87
################################################################################

# Specify the path to the linker script to use
ifneq (,$(filter $(TOOLCHAIN),GCC_ARM))
    LINKER_SCRIPT_EXT:=ld
else ifeq ($(TOOLCHAIN),ARM)
    LINKER_SCRIPT_EXT:=sct
    # Autogenerated file "cycfg_sau.c" uses default nsc region symbols
    # Bootloader  linker scripts do not have nsc region and it leads to build error
    # with the ARM compiler. Define default NSC_START_ADDRESS and NSC_END_ADDRESS
    # to suppress the build error.
    DEFINES+= NSC_START_ADDRESS=0x0
    DEFINES+= NSC_END_ADDRESS=0x100
    DEFINES+= NSC_SIZE=0x100
    # Suppress linker warnings (unused sections in the linker script)
    LDFLAGS+=--diag_suppress=L6314W,L6329W,L6244E
else ifeq ($(TOOLCHAIN),IAR)
    LINKER_SCRIPT_EXT:=icf
    # Enable variable length arrays
    CFLAGS+=--vla --diag_suppress Pa082,Pe550,Go004
    # Enable code copy for IAR toolchain
    DEFINES+=CY_INIT_CODECOPY_ENABLE
endif

-include ../bsps/TARGET_$(TARGET)/config/GeneratedSource/bootloader_linker_config.mk
# Path to the linker script to use (if empty, use the default linker script).
ifeq ($(LINKER_TYPE),SRAM)
    LINKER_SCRIPT=../bsps/TARGET_$(TARGET)/COMPONENT_$(CORE)/TOOLCHAIN_$(TOOLCHAIN)/bootloader_sram.$(LINKER_SCRIPT_EXT)
else
    LINKER_SCRIPT=../bsps/TARGET_$(TARGET)/COMPONENT_$(CORE)/TOOLCHAIN_$(TOOLCHAIN)/bootloader.$(LINKER_SCRIPT_EXT)
endif

# Default nsc_veneer file must be empty because bootloader does not have NSC region
NSC_VENEER=
################################################################################
# Paths
################################################################################

# Relative path to the project directory (default is the Makefile's directory).
#
# This controls where automatic source code discovery looks for code.
CY_APP_PATH=

# Relative path to the shared repo location.
#
# All .mtb files have the format, <URI>#<COMMIT>#<LOCATION>. If the <LOCATION> field 
# begins with $$ASSET_REPO$$, then the repo is deposited in the path specified by 
# the CY_GETLIBS_SHARED_PATH variable. The default location is one directory level 
# above the current app directory.
# This is used with CY_GETLIBS_SHARED_NAME variable, which specifies the directory name.
CY_GETLIBS_SHARED_PATH=../..

# Directory name of the shared repo location.
#
CY_GETLIBS_SHARED_NAME=mtb_shared

include $(CY_TOOLS_DIR)/make/start.mk
