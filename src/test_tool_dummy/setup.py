from setuptools import setup

package_name = 'test_tool_dummy'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    py_modules=[],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='You',
    maintainer_email='you@example.com',
    description='Dummy servers/publishers to test test_tool UI clients',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'a2_dummy = test_tool_dummy.a2_dummy:main'
        ],
    },
)
