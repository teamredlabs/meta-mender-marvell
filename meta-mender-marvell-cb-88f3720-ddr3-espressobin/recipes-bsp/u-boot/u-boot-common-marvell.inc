FILESEXTRAPATHS_prepend := "${THISDIR}/patches:"
SRC_URI_append = " file://0001-Set-HOSTARCH-and-ARCH-when-making-env-target.patch.manual"
MENDER_DTB_NAME = "fdt.dtb"

do_mender_uboot_auto_configure_fix () {
    patch ${WORKDIR}/uboot_auto_configure.sh ${WORKDIR}/0001-Set-HOSTARCH-and-ARCH-when-making-env-target.patch.manual
    sed -i 's/${ARCH}/'${TUNE_ARCH_32}'/g' ${WORKDIR}/uboot_auto_configure.sh
}

python () {
    if bb.utils.contains('MENDER_UBOOT_AUTO_CONFIGURE', '1', True, False, d):
        bb.build.addtask('do_mender_uboot_auto_configure_fix', 'do_mender_uboot_auto_configure', 'do_patch', d)
}
