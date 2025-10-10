# Auto-generated feature_config.mk file
# Configuration values derived from edgeprotect-bootloader-cfg-1.0.cypersonality
# Mbedtls Configuration Paths
DEFINES += MBEDTLS_CONFIG_FILE="\"$(SEARCH_ifx-mcuboot-pse84)/boot/platforms/COMPONENT_PSE84/mcuboot_config/ifx_mbedtls_crypto_config.h\""
DEFINES += MBEDTLS_PSA_CRYPTO_CONFIG_FILE="\"$(SEARCH_ifx-mcuboot-pse84)/boot/platforms/COMPONENT_PSE84/mcuboot_config/ifx_psa_crypto_config.h\""
DEFINES += MBEDTLS_USER_CONFIG_FILE="\"$(SEARCH_ifx-mcuboot-pse84)/boot/platforms/COMPONENT_PSE84/mcuboot_config/ifx_mbedtls_target_config.h\""

# HW rollback counter protection component

# Image validation component
COMPONENTS+=MCUBOOT_IMG_VALIDATION

# Image encryption component

# Measured boot component

# RRAM memory component
COMPONENTS+=MCUBOOT_RRAM_MEM

# SRAM memory component for RAM load

# SMIF Flash memory component
COMPONENTS+=MCUBOOT_SMIF_FLASH_MEM

# Random number generation component
COMPONENTS+=MCUBOOT_RNG
