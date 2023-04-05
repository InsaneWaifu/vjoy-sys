#[cfg(test)]
mod tests {
    #[test]
    fn open_device() {
        unsafe {
            //Success of this test can be observed via the vJoyMonitor and vJoyList executables bundled with vJoy.
            //Button 1 of device 1 will be set for one second and the Owner PID for device 1 will be set to this process.
            //After one second, button 1 of device 1 will be reset and the Owner PID for device 1 will be empty.

            let vjoy = vjoy_sys::vJoyInterface::new("C:/Program Files/vJoy/x64/vJoyInterface.dll")
                .unwrap();
            assert!(vjoy.vJoyEnabled() == 1, "vJoy is not installed");
            assert!(vjoy.isVJDExists(1) == 1, "device 1 does not exist");
            assert!(
                vjoy.AcquireVJD(1) == 1,
                "device 1 is busy and could not be acquired"
            );

            println!("Setting button 1 of device 1");
            assert!(
                vjoy.SetBtn(1, 1, 1) == 1,
                "button 1 of device 1 could not be set"
            );
            std::thread::sleep(std::time::Duration::from_millis(1000));

            println!("Resetting button 1 of device 1");
            assert!(
                vjoy.SetBtn(0, 1, 1) == 1,
                "button 1 of device 1 could not be reset"
            );
            std::thread::sleep(std::time::Duration::from_millis(1000));

            vjoy.RelinquishVJD(1);
        }
    }
}
